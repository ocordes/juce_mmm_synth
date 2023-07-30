/*
  ==============================================================================

    SliderWithLabel.cpp
    Created: 30 Jul 2023 2:09:04pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SliderWithLabel.h"

//==============================================================================
SliderWithLabel::SliderWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String paramId, juce::String labelName, const int width, const int height, juce::Slider::SliderStyle sliderStyle)
{
    sliderWidth = width;
    sliderHeight = height;
    
    slider.setSliderStyle (sliderStyle);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight );
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<SliderAttachment>(apvts, paramId, slider);
    
    
    label.setFont (fontHeight);
    label.setText (labelName, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

SliderWithLabel::~SliderWithLabel()
{
}

void SliderWithLabel::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SliderWithLabel::resized()
{
    const auto dialToLabelRatio = 15;
    const auto labelHeight = 18;
        
    jassert (sliderWidth > 0);
    jassert (sliderHeight > 0);
        
    label.setBounds (0, 0, sliderWidth, labelHeight);
    slider.setBounds (0, 0 + dialToLabelRatio, sliderWidth, sliderHeight);
}
