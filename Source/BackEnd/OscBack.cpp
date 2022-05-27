/*
  ==============================================================================

    OscilatorBack.cpp
    Created: 25 May 2022 5:35:51pm
    Author:  Илья

  ==============================================================================
*/

#include "OscBack.h"

void OscBack::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
	fmOperator.prepare(spec);
	prepare(spec);
}

void OscBack::setWaveType(const int choice)
{
	switch (choice)
	{
	case 0:
		initialise([](float x) {return std::sin(x); }); //Sine Wave
		break;
	case 1:
		initialise([](float x) {return x / juce::MathConstants<float>::pi; }); // Saw Wave
		break;
	case 2:
		initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; }); // Square Wave
		break;
	case 3:
		initialise([](float x) {return abs(x / juce::MathConstants<float>::pi); }); // Triangle Wave
		break;
	default:
		jassertfalse;
		break;
	}

}

void OscBack::setWaveFrequency(const int midiNoteNumber)
{
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
	lastMidiNote = midiNoteNumber;
}

void OscBack::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
	for (int chanel = 0; chanel < block.getNumChannels(); ++chanel)
	{
		for (int sample = 0; sample < block.getNumSamples(); ++sample)
		{
			fmMod = fmOperator.processSample(block.getSample(chanel, sample))*fmDepth;
		}
	}
	process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscBack::setFmParams(const float depth, const float freq)
{
	fmOperator.setFrequency(freq);
	fmDepth = depth;
	auto FreqNow = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
	setFrequency(FreqNow >= 0 ? FreqNow : FreqNow * -1.0f);
}