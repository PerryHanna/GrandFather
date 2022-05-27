/*
  ==============================================================================

    AdsrBack.h
    Created: 25 May 2022 2:43:30pm
    Author:  Илья

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrBack : public juce::ADSR
{
public:

    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:

    juce::ADSR::Parameters adsrParams;

};