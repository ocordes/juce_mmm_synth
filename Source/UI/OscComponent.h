/*
  ==============================================================================

    OscComponent.h
    Created: 14 Feb 2021 6:51:39pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"
#include "LookAndFeel.h"

//==============================================================================
/*
*/
class OscComponent : public CustomComponent
{
public:
    OscComponent (juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId, juce::String tuneId, juce::String fmPitchId, juce::String fmFreqId);
    ~OscComponent() override;

    void resized() override;

private:
    OtherLookAndFeel otherLookAndFeel;
    
    juce::ComboBox oscSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    
    SliderWithLabel gain;
    SliderWithLabel pitch;
    SliderWithLabel tune;
    SliderWithLabel fmFreq;
    SliderWithLabel fmDepth;
    
    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
