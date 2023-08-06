/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Juce_mmm_synthAudioProcessor::Juce_mmm_synthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams()
                       )
#endif
{
    synth.addSound(new SynthSound());
    
    for (int i = 0; i < numVoices; ++i)
    {
        synth.addVoice(new SynthVoice());
    }
    
    m_flogger = std::unique_ptr<juce::FileLogger>(juce::FileLogger::createDateStampedLogger("foo", "mylog", ".txt", "Welcome to plugin"));
}

Juce_mmm_synthAudioProcessor::~Juce_mmm_synthAudioProcessor()
{
}

//==============================================================================
const juce::String Juce_mmm_synthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Juce_mmm_synthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Juce_mmm_synthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Juce_mmm_synthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Juce_mmm_synthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Juce_mmm_synthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Juce_mmm_synthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Juce_mmm_synthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Juce_mmm_synthAudioProcessor::getProgramName (int index)
{
    return {};
}

void Juce_mmm_synthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Juce_mmm_synthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if ( auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void Juce_mmm_synthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Juce_mmm_synthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Juce_mmm_synthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
       
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // OSC controls
            // ADSR
            // LFO
            
            auto& oscWaveChoice = *apvts.getRawParameterValue ("OSC1");
            auto& fmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("OSC1FMFREQ");
            
            // Amp Adsr
            auto& attack = *apvts.getRawParameterValue ("ATTACK");
            auto& decay = *apvts.getRawParameterValue ("DECAY");
            auto& sustain = *apvts.getRawParameterValue ("SUSTAIN");
            auto& release = *apvts.getRawParameterValue ("RELEASE");
            
            // Filter
            auto& filterType = *apvts.getRawParameterValue ("FILTERTYPE");
            auto& frequency = *apvts.getRawParameterValue ("FILTERCUTOFF");
            auto& resonance = *apvts.getRawParameterValue ("FILTERRESONANCE");
            
            // Mod Adsr
            auto& modAttack = *apvts.getRawParameterValue ("MODATTACK");
            auto& modDecay = *apvts.getRawParameterValue ("MODDECAY");
            auto& modSustain = *apvts.getRawParameterValue ("MODSUSTAIN");
            auto& modRelease = *apvts.getRawParameterValue ("MODRELEASE");
            

            auto& osc = voice->getOscillator1();
            //auto& osc2 = voice->getOscillator2();
            for (int i = 0; i < getTotalNumOutputChannels(); i++)
            {
                osc[i].setWaveType (oscWaveChoice);
                osc[i].setFmParams (fmDepth, fmFreq);
            }
            
            voice->updateAdsr (attack.load(), decay.load(), sustain.load(), release.load());
            voice->updateFilter (filterType.load(), frequency.load(), resonance.load());
            voice->updateModAdsr (modAttack.load(), modDecay.load(), modSustain.load(), modRelease.load());
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Juce_mmm_synthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Juce_mmm_synthAudioProcessor::createEditor()
{
    return new Juce_mmm_synthAudioProcessorEditor (*this);
}

//==============================================================================
void Juce_mmm_synthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Juce_mmm_synthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Juce_mmm_synthAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout Juce_mmm_synthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // OSC select
    
    params.push_back (std::make_unique<juce::AudioParameterChoice> ("OSC1", "Oscillator", juce::StringArray { "Sine", "Saw", "Square", "Triangle" }, 0));
    
    // FM
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));
    
    
    // ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, }, 0.4f));
    
    // Filter ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODATTACK", "Mod Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODDECAY", "Mod Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODSUSTAIN", "Mod Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MODRELEASE", "Mod Release", juce::NormalisableRange<float> { 0.1f, 3.0f, }, 0.4f));
    
    
    // Filter
    params.push_back (std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray { "Low Pass", "Band Pass", "High Pass" }, 0));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 20.0f, "Hz"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERRESONANCE", "Filter Resonance", juce::NormalisableRange<float> { 0.1f, 7.0f, 0.1f }, 0.1f, ""));
    
    
    return { params.begin(), params.end() };
}
