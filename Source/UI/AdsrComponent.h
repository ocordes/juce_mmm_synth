/*
  ==============================================================================

    AdsrComponent.h
    Created: 23 Jul 2023 2:25:49pm
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
class AdsrComponent  : public CustomComponent
{
public:
    AdsrComponent (juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void resized() override;

private:
    static constexpr int sliderWidth { 50 };
    static constexpr int sliderHeight { 160 };
    
    SliderWithLabel attackSlider;
    SliderWithLabel decaySlider;
    SliderWithLabel sustainSlider;
    SliderWithLabel releaseSlider;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
