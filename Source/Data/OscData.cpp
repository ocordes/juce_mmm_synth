/*
  ==============================================================================

    OscData.cpp
    Created: 14 Feb 2021 6:51:17pm
    Author:  Joshua Hodge
 
    Updated:
    Oliver Cordes 2023-08-08

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    prepare (spec);
    fmOsc.prepare (spec);
    gain.prepare (spec);    
}

void OscData::setType (const int oscSelection)
{
    switch (oscSelection)
    {
        // Sine
        case 0:
            initialise ([](float x) { return std::sin (x); });
            break;
            
        // Saw
        case 1:
            initialise ([] (float x) { return x / juce::MathConstants<float>::pi; });
            break;
          
        // Square
        case 2:
            initialise ([] (float x) { return x < 0.0f ? -1.0f : 1.0f; });
            break;
            
        // Triangle
        case 3:
            initialise ([](float x) { return abs(x / juce::MathConstants<float>::pi); } );
            break;
            
        default:
            // You shouldn't be here!
            jassertfalse;
            break;
    }
}

void OscData::setGain (const float levelInDecibels)
{
    gain.setGainDecibels (levelInDecibels);
}

void OscData::setOscPitch (const int pitch)
{
    lastPitch = pitch;
    //setFrequency (juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch) + fmModulator));
    float newFreq = juce::MidiMessage::getMidiNoteInHertz (lastMidiNote + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
}


void OscData::setOscTune (const int tune)
{
    float ftune = tune * 0.010f;
    DBG(tune);
    lastTune = std::pow (2, ftune/1200);

    float newFreq = juce::MidiMessage::getMidiNoteInHertz (lastMidiNote + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
}


void OscData::setFreq (const int midiNoteNumber)
{
    //setFrequency (juce::MidiMessage::getMidiNoteInHertz ((midiNoteNumber + lastPitch) + fmModulator));
    float newFreq = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
    lastMidiNote = midiNoteNumber;
}

void OscData::setFmOsc (const float freq, const float depth)
{
    fmDepth = depth;
    fmOsc.setFrequency (freq);
    //setFrequency (juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch) + fmModulator));
    float newFreq = juce::MidiMessage::getMidiNoteInHertz (lastMidiNote + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
}

void OscData::renderNextBlock (juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert (audioBlock.getNumSamples() > 0);
    process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
}

float OscData::processNextSample (float input)
{
    fmModulator = fmOsc.processSample (input) * fmDepth;
    return gain.processSample (processSample (input));
}

void OscData::setParams (const int oscChoice, const float oscGain, const int oscPitch, const int oscTune, const float fmFreq, const float fmDepth)
{
    setType (oscChoice);
    setGain (oscGain);
    setOscPitch (oscPitch);
    setOscTune (oscTune);
    setFmOsc (fmFreq, fmDepth);
}

void OscData::resetAll()
{
    reset();
    fmOsc.reset();
    gain.reset();
}
