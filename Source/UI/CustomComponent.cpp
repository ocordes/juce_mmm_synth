/*
  ==============================================================================

    CustomComponent.cpp
    Created: 30 Jul 2023 3:15:29pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomComponent.h"

//==============================================================================
CustomComponent::CustomComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomComponent::~CustomComponent()
{
}

void CustomComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    auto bounds = getLocalBounds();
    g.setColour (boundsColour);
    g.drawRoundedRectangle (bounds.toFloat().reduced (10.0f), 5.0f, 2.0f);
        
    g.setColour (juce::Colours::yellow);
    g.setFont (fontHeight);
    g.setFont (g.getCurrentFont().boldened());
        
    jassert (name.isNotEmpty());
    g.drawText (name, 20, 15, 100, 25, juce::Justification::left);
}

void CustomComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
