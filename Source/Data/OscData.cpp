/*
  ==============================================================================

    OscData.cpp
    Created: 23 Jul 2023 3:46:40pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
    resetAll();
    
    prepare (spec);
    fmOsc.prepare (spec);
    gain.prepare (spec);
}


void OscData::setType (const int choice)
{
    switch (choice) {
        case 0:
            // sine wave
            initialise ([](float x) {return std::sin (x);} );
            break;
        case 1:
            // saw wave
            initialise ([](float x) {return x / juce::MathConstants<float>::pi;} );
            break;
        case 2:
            // square wave
            initialise ([](float x) {return x < 0.0f ? -1.0f : 1.0f;} );
            break;
            
        case 3:
            // triangle wave
            initialise ([](float x) { return abs(x / juce::MathConstants<float>::pi); } );
            break;
        default:
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
    float newFreq = juce::MidiMessage::getMidiNoteInHertz (lastMidiNote + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
}


void OscData::setOscTune (const int tune)
{
    float ftune = tune * 0.01f;
    lastTune = std::pow (2, ftune/1200);
    
    float newFreq = juce::MidiMessage::getMidiNoteInHertz (lastMidiNote + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
}


void OscData::setFreq (const int midiNoteNumber)
{
    float newFreq = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
    lastMidiNote = midiNoteNumber;
}


void OscData::setFmOsc (const float freq, const float depth)
{
    fmDepth = depth;
    fmOsc.setFrequency (freq);
    float newFreq = juce::MidiMessage::getMidiNoteInHertz (lastMidiNote + lastPitch) + fmModulator;
    setFrequency (newFreq * lastTune);
}


void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        for (int s = 0; s < block.getNumSamples(); ++s)
        {
            fmModulator = fmOsc.processSample(block.getSample(channel, s)) * fmDepth;
        }
    }
    
    process (juce::dsp::ProcessContextReplacing<float> (block));
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


void OscData::resetAll ()
{
    reset();
    fmOsc.reset();
    gain.reset();
}
