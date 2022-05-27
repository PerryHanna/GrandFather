/*
  ==============================================================================

    AdsrBack.cpp
    Created: 25 May 2022 2:43:30pm
    Author:  Илья

  ==============================================================================
*/

#include "AdsrBack.h"
void AdsrBack::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams); 
}
