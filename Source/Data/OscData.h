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
    void prepareToPlay(juce::dsp::ProcessSpec &spec);
    void setWaveType (const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams (const float depth, const float freq);
    
    float processNextSample (float input);
    
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) {return std::sin (x);} };
    
    float fmMod { 0.0f };
    float fmDepth { 0.0f };
    int   lastMidiNote { 0 };
};
