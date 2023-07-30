/*
  ==============================================================================

    FilterComponent.cpp
    Created: 30 Jul 2023 4:01:25pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterSelectorID, juce::String cutoffId, juce::String resonanceId)
:cutoffSlider (apvts, cutoffId, "CutOff Freq", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
resonanceSlider (apvts, resonanceId, "Resonance", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    juce::StringArray choices {"Low pass", "Band pass", "High pass"};
    filterSelector.addItemList (choices, 1);
    
    addAndMakeVisible (filterSelector);
    
    filterSelectorAttachment = std::make_unique<ComboBoxAttachment>(apvts, filterSelectorID, filterSelector);
    
    addAndMakeVisible(cutoffSlider);
    addAndMakeVisible(resonanceSlider);
}

FilterComponent::~FilterComponent()
{
}


void FilterComponent::resized()
{
    const auto sliderPosY = 15;
    const auto sliderWidth = 70;
    const auto sliderHeight = 88;
    
    filterSelector.setBounds  (18, 40, 100, 25);
    cutoffSlider.setBounds (120, sliderPosY, sliderWidth, sliderHeight);
    resonanceSlider.setBounds (190, sliderPosY, sliderWidth, sliderHeight);
}
