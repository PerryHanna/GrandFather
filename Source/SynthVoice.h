/*
  ==============================================================================

    SynthVoice.h
    Created: 23 May 2022 10:08:36pm
    Author:  Илья

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "BackEnd/AdsrBack.h"
#include "BackEnd/OscBack.h"


class SynthVoice :public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTaiOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChanels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    void update(const float attack, const float decay, const float sustain, const float release);
    OscBack& getOscilator() { return osc; }
private:

    AdsrBack adsr;
    juce::AudioBuffer<float> synthBuffer;

    OscBack osc;
    
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};