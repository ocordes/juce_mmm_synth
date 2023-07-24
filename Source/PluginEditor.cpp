/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Juce_mmm_synthAudioProcessorEditor::Juce_mmm_synthAudioProcessorEditor (Juce_mmm_synthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.apvts), osc (audioProcessor.apvts, "OSC")
{
    setSize (400, 300);
    
    addAndMakeVisible (adsr);
    addAndMakeVisible (osc);
}

Juce_mmm_synthAudioProcessorEditor::~Juce_mmm_synthAudioProcessorEditor()
{
}

//==============================================================================
void Juce_mmm_synthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void Juce_mmm_synthAudioProcessorEditor::resized()
{
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    osc.setBounds(10, 10, 90, 30);
}

