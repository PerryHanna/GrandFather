/*
  ==============================================================================

    FilterFront.cpp
    Created: 27 May 2022 12:07:18am
    Author:  Илья

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterFront.h"

//==============================================================================
FilterFront::FilterFront(juce::AudioProcessorValueTreeState& apvts, juce::String filterSelectId, juce::String filterCutoffId,
    juce::String filterResonaceId)
{
    juce::StringArray choices{ "LowPass", "HightPass", "BandPass" };
    filterSelect.addItemList(choices, 1);
    addAndMakeVisible(filterSelect);

    fillterSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterSelectId, filterSelect);

    setSliderParams(filterCutoffSlider, filterCutoffLabel, apvts, filterCutoffId, filterCutoffSliderAttachment);
    setSliderParams(filterResonaceSlider, filterResonaceLabel, apvts, filterResonaceId, filterResonaceSliderAttachment);
}

FilterFront::~FilterFront()
{
}

void FilterFront::paint (juce::Graphics& g)
{

}

void FilterFront::resized()
{
    filterSelect.setBounds(getWidth() / 2 - 45, 5, 90, 20);

    filterCutoffSlider.setBounds(0, 45, 100, 90);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - 20, filterCutoffSlider.getWidth() + 10, 20);

    filterResonaceSlider.setBounds(filterCutoffSlider.getRight(), 45, 100, 90);
    filterResonaceLabel.setBounds(filterResonaceSlider.getX(), filterResonaceSlider.getY() - 20, filterResonaceSlider.getWidth(), 20);
}

void FilterFront::setSliderParams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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
