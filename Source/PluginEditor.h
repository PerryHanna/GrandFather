/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FrontEnd/AdsrFront.h"
#include "FrontEnd/OscFront.h"
#include "FrontEnd/FilterFront.h"

//==============================================================================
/**
*/
class ClassSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ClassSynthAudioProcessorEditor (ClassSynthAudioProcessor&);
    ~ClassSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ClassSynthAudioProcessor& audioProcessor;
    OscFront osc;
    AdsrFront adsr;
    FilterFront filter;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClassSynthAudioProcessorEditor)
};
