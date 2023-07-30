/*
  ==============================================================================

    SliderWithLabel.h
    Created: 30 Jul 2023 2:09:04pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

class SliderWithLabel  : public juce::Component
{
public:
    SliderWithLabel (juce::AudioProcessorValueTreeState& apvts, juce::String paramId, juce::String labelName, const int width, const int height, juce::Slider::SliderStyle sliderStyle);
    ~SliderWithLabel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    static constexpr float fontHeight { 15.0f };
    static constexpr int textBoxWidth { 48 };
    static constexpr int textBoxHeight { 20 };
    
    
    juce::Slider slider;
    juce::Label  label;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attachment;
    
    int sliderWidth = { 0 };
    int sliderHeight = { 0 };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderWithLabel)
};
