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
        osc[i].setWaveFrequency(midiNoteNumber);
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
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    for (int ch = 0; ch < numChannelsToProcess; ch++)
    {
        osc[ch].prepareToPlay (spec);
    }
    adsr.setSampleRate(sampleRate);
    filter.prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
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
    
    if (startSample > 0)
    {
        DBG(startSample);
        DBG(numSamples);
    }
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    modAdsr.applyEnvelopeToBuffer (outputBuffer, 0, numSamples);   // activate the modAdsr no really buffer changes
    synthBuffer.clear();
    
    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer (ch, 0);
            
        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = osc[ch].processNextSample (buffer[s]); // + osc2[ch].processNextSample (buffer[s]);
        }
    }
        
    
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    
    
    
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    
    
    filter.process (synthBuffer);
    
    
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

void SynthVoice::updateFilter (const int filterType, const float frequency, const float resonance)
{
    float modulator = modAdsr.getNextSample();
    filter.updateParameters(filterType, frequency, resonance, modulator);
}


void SynthVoice::updateModAdsr (const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR (attack, decay, sustain, release);
}
