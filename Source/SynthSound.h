/*
  ==============================================================================

    SynthSound.h
    Created: 16 Jul 2023 3:05:54pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
    bool     appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool     appliesToChannel (int midiChannel) override
    {
        return true;
    }
};
