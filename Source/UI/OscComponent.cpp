/*
  ==============================================================================

    OscComponent.cpp
    Created: 24 Jul 2023 2:47:28pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String fmFreqID, juce::String fmDepthId)
: fmFreqSlider (apvts, fmFreqID, "FM Freq", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
fmDepthSlider (apvts, fmDepthId, "FM Depth", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    juce::StringArray choices {"Sine", "Saw", "Square", "Triangle"};
    oscWaveSelector.addItemList (choices, 1);
    
    addAndMakeVisible (oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    
    addAndMakeVisible(fmFreqSlider);
    addAndMakeVisible(fmDepthSlider);
}

OscComponent::~OscComponent()
{
}


void OscComponent::resized()
{
    const auto sliderPosY = 15;
    const auto sliderWidth = 70;
    const auto sliderHeight = 88;
    
    oscWaveSelector.setBounds  (18, 40, 100, 25);
    fmFreqSlider.setBounds (120, sliderPosY, sliderWidth, sliderHeight);
    fmDepthSlider.setBounds (190, sliderPosY, sliderWidth, sliderHeight);
}
