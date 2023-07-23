/*
  ==============================================================================

    SynthVoice.h
    Created: 16 Jul 2023 3:05:08pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"



class SynthVoice : public juce::SynthesiserVoice
{
public:
    
    bool canPlaySound (juce::SynthesiserSound *sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
    
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    juce::AudioBuffer<float> synthBuffer;
    
    
    //juce::dsp::Oscillator<float> osc { [](float x) { return std::sin (x); }};
    juce::dsp::Oscillator<float> osc { [](float x) {return x / juce::MathConstants<float>::pi; }};
    //juce::dsp::Oscillator<float> osc { [](float x) { return x < 0.0f ? -1.0f : 1.0f; }, 200 };
    juce::dsp::Gain<float> gain;
    bool isPrepared { false };
        
    // return std::sin (x); //Sine Wave
    // return x / MathConstants<float>::pi; // Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f;  // Square Wave
};
