/*
  ==============================================================================

    FilterData.h
    Created: 30 Jul 2023 11:31:53am
    Author:  Oliver Cordes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class FilterData
{
public:
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels);
    void process (juce::AudioBuffer<float>& buffer);
    float processNextSample (int channel, float inputValue);
    void updateParameters (const int filterType, const float frequency, const float resonance);
    void reset ();
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    
    bool isPrepared { false };
    
};
