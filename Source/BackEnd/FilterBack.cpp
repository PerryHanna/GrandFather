/*
  ==============================================================================

    FilterBack.cpp
    Created: 27 May 2022 12:06:55am
    Author:  Илья

  ==============================================================================
*/

#include "FilterBack.h"

void FilterBack::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    filter.prepare(spec);

    isPrepared = true;
}

void FilterBack::process(juce::AudioBuffer<float>& buffer)
{ 
    jassert(isPrepared);

    juce::dsp::AudioBlock <float> block{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float> {block});
}

void FilterBack::updateParameters(const int filterType, const float frequency, const float resonance)
{
    switch (filterType)
    {
    case 0:
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    case 1:
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    case 2:
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
    }
    filter.setCutoffFrequency(frequency);
    filter.setResonance(resonance);
}

void FilterBack::reset()
{
    filter.reset();
}