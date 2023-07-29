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
{
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList (choices, 1);
    
    addAndMakeVisible (oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    
    
    setSliderWithLabel (fmFreqSlider, fmFreqLabel, apvts, fmFreqID, fmFreqAttachment);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(0, 0, 90, 20);
    fmFreqSlider.setBounds (0, 80, 100, 90);
    fmFreqLabel.setBounds (fmFreqSlider.getX(), fmFreqSlider.getY()-20, fmFreqSlider.getWidth(), 20);
}


void OscComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}
