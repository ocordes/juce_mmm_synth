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
    void setType (const int choice);
    void setGain (const float levelInDecibels);
    void setOscPitch (const int pitch);
    void setOscTune (const int tune);
    void setFreq (const int midiNoteNumber);
    void setFmOsc (const float depth, const float freq);

    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    float processNextSample (float input);

    void setParams (const int oscChoice, const float oscGain, const int oscPitch, const int oscTune, const float fmFreq, const float fmDepth);
    void resetAll();
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); }};
    juce::dsp::Gain<float> gain;
    int lastPitch { 0 };
    float lastTune { 1.0f }; 
    int lastMidiNote { 0 };
    float fmDepth { 0.0f };
    float fmModulator { 0.0f };
};
