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
, osc1 (audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1PITCH", "OSC1TUNE", "OSC1FMFREQ", "OSC1FMDEPTH")
, osc2 (audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2PITCH", "OSC2TUNE", "OSC2FMFREQ", "OSC2FMDEPTH")
, adsr (audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE")
, modAdsr (audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
{
    setSize (800, 550);
    
    osc1.setName ("OSC 1");
    addAndMakeVisible (osc1);
    
    osc2.setName ("OSC 2");
    addAndMakeVisible (osc2);
    
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
    //const auto width = 300;
   // const auto height = 200;
    
    osc1.setBounds (0, 0, 500, 120);
    osc2.setBounds (0, 130, 500, 120);
    adsr.setBounds (510, 0, 300, 260);
    modAdsr.setBounds (510, 260, 300, 260);
    filter.setBounds (0, 260, 500, 260);
    
}

