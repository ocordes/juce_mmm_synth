/*
  ==============================================================================

    OscComponent.h
    Created: 24 Jul 2023 2:47:28pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"
#include "SliderWithLabel.h"

//==============================================================================
/*
*/
class OscComponent  : public CustomComponent
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String gainId, juce::String pitchId, juce::String tuneId, juce::String fmFreqID, juce::String fmDepthId);
    ~OscComponent() override;

    void resized() override;

private:
    static constexpr int dialWidth { 70 };
    static constexpr int dialHeight { 70 };
    
    
    juce::ComboBox oscWaveSelector;
    juce::Label    oscWaveLabel { "Wave", "Wave"};
    
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<ComboBoxAttachment> oscWaveSelectorAttachment;
    
    SliderWithLabel gainSlider;
    SliderWithLabel pitchSlider;
    SliderWithLabel tuneSlider;
    SliderWithLabel fmFreqSlider;
    SliderWithLabel fmDepthSlider;
   
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
