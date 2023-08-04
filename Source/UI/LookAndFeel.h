/*
  ==============================================================================

    LookAndFeel.h
    Created: 4 Aug 2023 2:53:11pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel();
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;
    
private:
    juce::Image knobImage_red;
    juce::Image knobImage_green;
    juce::Image knobImage_blue;
};
