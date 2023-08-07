/*
  ==============================================================================

    SynthVoice.cpp
    Created: 16 Jul 2023 3:05:08pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include "SynthVoice.h"

#include <JuceHeader.h>

#include "SynthSound.h"


SynthVoice::SynthVoice()
: juce::SynthesiserVoice()
{
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound *sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}


void SynthVoice::startNote (int midiNoteNumber, float velocity,
                                juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    for (int i = 0; i < numChannelsToProcess; ++i)
    {
        osc1[i].setFreq (midiNoteNumber);
        osc2[i].setFreq (midiNoteNumber);
    }
    adsr.noteOn();
    modAdsr.noteOn();
}


void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();
    
    if ( ! allowTailOff || ! adsr.isActive() )
        clearCurrentNote();
    
}


void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}


void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}


void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();
    
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    for (int ch = 0; ch < numChannelsToProcess; ch++)
    {
        osc1[ch].prepareToPlay (spec);
        osc2[ch].prepareToPlay (spec);
        filter[ch].prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
    }

    modAdsr.setSampleRate (sampleRate);
    gain.prepare (spec);
    
    gain.setGainLinear (0.3f);
    
    
    isPrepared = true;
}


void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}


void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer,
                                      int startSample, int numSamples)
{
    jassert(isPrepared);
    
    if ( ! isVoiceActive())
        return;
    
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    modAdsr.applyEnvelopeToBuffer (outputBuffer, 0, numSamples);   // activate the modAdsr no really buffer changes
    
    modAdsrOutput = modAdsr.getNextSample();
    
    synthBuffer.clear();
    
    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer (ch, 0);
            
        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = osc1[ch].processNextSample (buffer[s]) + osc2[ch].processNextSample (buffer[s]);
        }
    }
        
    
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    
    
    
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    
    
    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer (ch, 0);
        
        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = filter[ch].processNextSample (ch, synthBuffer.getSample
                                                      (ch, s));
        }
    }
    
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        
        if ( ! adsr.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::reset()
{
    gain.reset();
    adsr.reset();
    modAdsr.reset();
}

void SynthVoice::updateFilter (const int filterType, const float filterCutoff, const float resonance)
{
    float  adsrDepth { 1.0f };
    
    auto cutoff = (adsrDepth * modAdsrOutput) + filterCutoff;
    cutoff = std::clamp<float> (cutoff, 20.0f, 20000.0f);
    
    for (int ch = 0; ch < numChannelsToProcess; ++ch)
    {
        filter[ch].updateParameters(filterType, cutoff, resonance);
    }
}


void SynthVoice::updateModAdsr (const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR (attack, decay, sustain, release);
}
