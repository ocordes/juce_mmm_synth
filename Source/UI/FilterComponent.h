/*
  ==============================================================================

    FilterComponent.h
    Created: 30 Jul 2023 4:01:25pm
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
class FilterComponent  : public CustomComponent
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterSelectorID, juce::String cutoffId, juce::String resonanceId);
    ~FilterComponent() override;

    void resized() override;

private:
    static constexpr int dialWidth { 70 };
    static constexpr int dialHeight { 70 };
    
    juce::ComboBox filterSelector;
    
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<ComboBoxAttachment> filterSelectorAttachment;
    
    
    SliderWithLabel cutoffSlider;
    SliderWithLabel resonanceSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
