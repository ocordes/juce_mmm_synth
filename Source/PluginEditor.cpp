/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Juce_mmm_synthAudioProcessorEditor::Juce_mmm_synthAudioProcessorEditor (Juce_mmm_synthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.apvts), filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE"), osc (audioProcessor.apvts, "OSC1", "OSC1FMFREQ", "OSC1FMDEPTH")
{
    setSize (600, 300);
    
    adsr.setName ("Envelope");
    addAndMakeVisible (adsr);
    
    filter.setName ("Filter");
    addAndMakeVisible (filter);
    
    osc.setName ("OSC 1");
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
    adsr.setBounds (310, 0, 250, 250);
    filter.setBounds (0, 130, 300, 120);
    osc.setBounds (0, 0, 300, 120);
}

