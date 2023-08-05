/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 23 Jul 2023 2:25:49pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent (juce::AudioProcessorValueTreeState& apvts, juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID)
: attackSlider(apvts, attackID, "A", sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical),
decaySlider(apvts, decayID, "D", sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical),
sustainSlider(apvts, sustainID, "S", sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical),
releaseSlider(apvts, releaseID, "R", sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical)
{
    addAndMakeVisible (attackSlider);
    addAndMakeVisible (decaySlider);
    addAndMakeVisible (sustainSlider);
    addAndMakeVisible (releaseSlider);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::resized()
{
    const auto startX = 15;
    const auto startY = 55;
    const auto width = sliderWidth;
    const auto height = sliderHeight + 20;
        
    attackSlider.setBounds (startX, startY, width, height);
    decaySlider.setBounds (attackSlider.getRight(), startY, width, height);
    sustainSlider.setBounds (decaySlider.getRight(), startY, width, height);
    releaseSlider.setBounds (sustainSlider.getRight(), startY, width, height);
}
