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
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:
    SynthVoice();
    bool canPlaySound (juce::SynthesiserSound *sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void reset();
        
    void updateAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateFilter (const int filterType, const float filterCutoff, const float resonance);
    void updateModAdsr(const float attack, const float decay, const float sustain, const float release);
    
    std::array<OscData, 2>& getOscillator1() { return osc1; }
    std::array<OscData, 2>& getOscillator2() { return osc2; }
    

private:
    static constexpr int numChannelsToProcess { 2 };
    
    std::array<OscData, numChannelsToProcess> osc1;
    std::array<OscData, numChannelsToProcess> osc2;
    std::array<FilterData, numChannelsToProcess> filter;
    
    juce::AudioBuffer<float> synthBuffer;
    
    AdsrData adsr;
    AdsrData modAdsr;
    
    float modAdsrOutput { 0.0f };
    
    
    juce::dsp::Gain<float> gain;
    bool isPrepared { false };
};
