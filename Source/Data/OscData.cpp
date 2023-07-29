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
    fmOsc.prepare (spec);
    prepare (spec);
}

void OscData::setWaveType (const int choice)
{
    // return std::sin (x); //Sine Wave
    // return x / MathConstants<float>::pi; // Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f;  // Square Wave
    
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
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency (juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidiNote = midiNoteNumber;
}


void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        for (int s = 0; s < block.getNumSamples(); ++s)
        {
            fmMod = fmOsc.processSample(block.getSample(channel, s)) * fmDepth;
        }
    }
    
    process (juce::dsp::ProcessContextReplacing<float> (block));
}


void OscData::setFmParams (const float depth, const float freq)
{
    fmOsc.setFrequency (freq);
    fmDepth = depth;
    setFrequency (juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod);
}
