/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"

//==============================================================================
/**
*/
class Juce_mmm_synthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Juce_mmm_synthAudioProcessorEditor (Juce_mmm_synthAudioProcessor&);
    ~Juce_mmm_synthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Juce_mmm_synthAudioProcessor& audioProcessor;
    AdsrComponent adsr;
    OscComponent osc;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Juce_mmm_synthAudioProcessorEditor)
};
