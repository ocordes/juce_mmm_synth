/*
  ==============================================================================

    OscData.cpp
    Created: 23 Jul 2023 3:46:40pm
    Author:  Oliver Cordes

  ==============================================================================
*/

#include "OscData.h"


void OscData::setWaveType (const int choice)
{
    // return std::sin (x); //Sine Wave
    // return x / MathConstants<float>::pi; // Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f;  // Square Wave
    
    switch (choice) {
        case 0:
            // sine wave
            break;
        case 1:
            // saw wave
            break;
        case 2:
            // square wave
            break;
            
        default:
            break;
    }
}
