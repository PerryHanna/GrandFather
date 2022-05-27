/*
  ==============================================================================

    FilterBack.h
    Created: 27 May 2022 12:06:55am
    Author:  Илья

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterBack
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int filterType, const float frequency, const float resonance);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};