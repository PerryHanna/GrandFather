/*
  ==============================================================================

    SynthSound.h
    Created: 23 May 2022 10:09:31pm
    Author:  Илья

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound :public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

};