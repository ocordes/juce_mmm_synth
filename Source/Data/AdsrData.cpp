/*
  ==============================================================================

    AdsrData.cpp
    Created: 23 Jul 2023 2:26:35pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include "AdsrData.h"


void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters (adsrParams);
}
