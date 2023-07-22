/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    juce::Slider  attackSlider;
    juce::Slider  decaySlider;
    juce::Slider  sustainSlider;
    juce::Slider  releaseSlider;
    juce::ComboBox oscSelector;
    
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    std::unique_ptr<ComboBoxAttachment> oscSelAttachment;
    
    Juce_mmm_synthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Juce_mmm_synthAudioProcessorEditor)
};
