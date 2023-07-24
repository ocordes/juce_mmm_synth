/*
  ==============================================================================

    OscData.h
    Created: 23 Jul 2023 3:46:40pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void setWaveType (const int choice);
    
private:
};
