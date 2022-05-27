/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ClassSynthAudioProcessorEditor::ClassSynthAudioProcessorEditor(ClassSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), osc(audioProcessor.apvts, "OSC", "FMFREQ", "FMDEPTH"),
    adsr(audioProcessor.apvts), filter(audioProcessor.apvts, "FILTER", "FILTERCUTOFF", "FILTERRES")
{
    setSize (400, 300);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
}

ClassSynthAudioProcessorEditor::~ClassSynthAudioProcessorEditor()
{
}

//==============================================================================
void ClassSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkslategrey);
}

void ClassSynthAudioProcessorEditor::resized()
{
    filter.setBounds(0, getHeight() / 2, getWidth() / 2, getHeight() / 2);
    osc.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    adsr.setBounds(getWidth() / 2 + 15, 10, getWidth()/2, getHeight()/2);
    
   
}