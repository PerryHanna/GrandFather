/*
  ==============================================================================

    OscFront.cpp
    Created: 25 May 2022 6:54:52pm
    Author:  Илья

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscFront.h"

//==============================================================================
OscFront::OscFront(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectId, juce::String fmFreqId, juce::String fmDepthId)
{
    juce::StringArray choices{ "Sine", "Saw", "Square", "Triangle" };
    oscWaveSelect.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelect);
    oscWaveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,waveSelectId, oscWaveSelect);

    setSliderParams(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqSliderAttachment);
    setSliderParams(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthSliderAttachment);
}

OscFront::~OscFront()
{
}

void OscFront::paint (juce::Graphics& g)
{
   
}

void OscFront::resized()
{
    oscWaveSelect.setBounds(getWidth()/2 - 45, 5, 90, 20);

    fmFreqSlider.setBounds(0, 45, 100, 90);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - 20, fmFreqSlider.getWidth(), 20);

    fmDepthSlider.setBounds(fmFreqSlider.getRight(), 45, 100, 90);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - 20, fmDepthSlider.getWidth(), 20);
}

void OscFront::setSliderParams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
