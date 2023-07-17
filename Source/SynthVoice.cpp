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



bool SynthVoice::canPlaySound (juce::SynthesiserSound *sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}


void SynthVoice::startNote (int midiNoteNumber, float velocity,
                                juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    
}


void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    
}


void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}


void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}


void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    //spec.numChannels = getTotalNumOutputChannels();
    
    osc.prepare (spec);
    gain.prepare (spec);
    
    osc.setFrequency (220.0f);
    gain.setGainLinear (0.01f);
}


void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer,
                                      int startSample, int numSamples)
{
    
}
