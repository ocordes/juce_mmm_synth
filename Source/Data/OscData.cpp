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


float OscData::processNextSample (float input)
{
    //fmModulator = fmOsc.processSample (input) * fmDepth;
    fmMod = fmOsc.processSample (input) * fmDepth;
    //return gain.processSample (processSample (input));
    return processSample (input);
}


void OscData::setFmParams (const float depth, const float freq)
{
    fmOsc.setFrequency (freq);
    fmDepth = depth;
    auto currentFrequency = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
    setFrequency (currentFrequency >= 0 ? currentFrequency : currentFrequency * -1.0f);
}
