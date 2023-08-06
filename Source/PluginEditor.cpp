/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Juce_mmm_synthAudioProcessorEditor::Juce_mmm_synthAudioProcessorEditor (Juce_mmm_synthAudioProcessor& p)
: AudioProcessorEditor (&p)
, audioProcessor (p)
, osc (audioProcessor.apvts, "OSC1", "OSC1FMFREQ", "OSC1FMDEPTH")
, adsr (audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE")
, modAdsr (audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
{
    setSize (600, 550);
    
    osc.setName ("OSC 1");
    addAndMakeVisible (osc);
    
    adsr.setName ("Amp Envelope");
    addAndMakeVisible (adsr);
    
    filter.setName ("Filter");
    addAndMakeVisible (filter);
    
    modAdsr.setName ("Mod Envelope");
    addAndMakeVisible (modAdsr);
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
    const auto width = 300;
    const auto height = 200;
    
    osc.setBounds (0, 0, 300, 120);
    adsr.setBounds (310, 0, 300, 260);
    modAdsr.setBounds (310, 260, 300, 260);
    filter.setBounds (0, 260, 300, 260);
    
}

