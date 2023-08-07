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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String gainId, juce::String pitchId, juce::String tuneId, juce::String fmFreqID, juce::String fmDepthId)
: gainSlider (apvts, gainId, "OSC Gain", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
, pitchSlider (apvts, pitchId, "OSC Pitch", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
, tuneSlider (apvts, tuneId, "OSC Tune", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
, fmFreqSlider (apvts, fmFreqID, "FM Freq", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
, fmDepthSlider (apvts, fmDepthId, "FM Depth", dialWidth, dialHeight, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    juce::StringArray choices {"Sine", "Saw", "Square", "Triangle"};
    oscWaveSelector.addItemList (choices, 1);
    
    addAndMakeVisible (oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    
    addAndMakeVisible (gainSlider);
    addAndMakeVisible (pitchSlider);
    addAndMakeVisible (tuneSlider);
    addAndMakeVisible (fmFreqSlider);
    addAndMakeVisible (fmDepthSlider);
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
    gainSlider.setBounds (120, sliderPosY, sliderWidth, sliderHeight);
    pitchSlider.setBounds (190, sliderPosY, sliderWidth, sliderHeight);
    tuneSlider.setBounds (260, sliderPosY, sliderWidth, sliderHeight);
    fmFreqSlider.setBounds (330, sliderPosY, sliderWidth, sliderHeight);
    fmDepthSlider.setBounds (400, sliderPosY, sliderWidth, sliderHeight);
}
