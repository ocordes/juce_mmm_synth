/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 4 Aug 2023 2:53:11pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include "LookAndFeel.h"

#include <JuceHeader.h>


OtherLookAndFeel::OtherLookAndFeel()
{
    knobImage_red = juce::ImageFileFormat::loadFrom(BinaryData::knobs1_red_png, BinaryData::knobs1_red_pngSize);
    knobImage_green = juce::ImageFileFormat::loadFrom(BinaryData::knobs1_green_png, BinaryData::knobs1_green_pngSize);
    knobImage_blue = juce::ImageFileFormat::loadFrom(BinaryData::knobs1_blue_png, BinaryData::knobs1_blue_pngSize);
}


void OtherLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider)
{
    juce::Image& knobImage = knobImage_red;
    
    int knobWidth = knobImage.getWidth();
    int knobHeight = knobImage.getHeight();
    
    int nr_images = int(knobWidth/knobHeight);   // assume the images a squares
    
    int current_image = int((nr_images-1)*sliderPos);
    
    auto img = knobImage.getClippedImage(juce::Rectangle<int>(current_image*knobHeight,0,knobHeight,knobHeight));
    
    g.drawImageAt(img, x+(width-knobHeight)/2, y+(height-knobHeight)/2);
}
