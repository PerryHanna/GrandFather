/*
  ==============================================================================

    AdsrFront.cpp
    Created: 25 May 2022 2:42:58pm
    Author:  Илья

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrFront.h"

//==============================================================================
AdsrFront::AdsrFront(juce::AudioProcessorValueTreeState& apvts)
{
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (apvts, "RELEASE", releaseSlider);

    setSliderParams(attackSlider, attackSliderLabel);
    setSliderParams(decaySlider, decaySliderLabel);
    setSliderParams(sustainSlider, sustainSliderLabel);
    setSliderParams(releaseSlider, releaseSliderLabel);

    
}

AdsrFront::~AdsrFront()
{
}

void AdsrFront::paint (juce::Graphics& g)
{
 
}

void AdsrFront::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    attackSliderLabel.setBounds(attackSlider.getX(), attackSlider.getY() - 10, attackSlider.getWidth() + 10, 20);
    decaySliderLabel.setBounds(decaySliderLabel.getX(), decaySliderLabel.getY() - 10, decaySliderLabel.getWidth() + 10, 20);
    sustainSliderLabel.setBounds(sustainSliderLabel.getX(), sustainSliderLabel.getY() - 10, sustainSliderLabel.getWidth() + 10, 20);
    releaseSliderLabel.setBounds(releaseSliderLabel.getX(), releaseSliderLabel.getY() - 10, releaseSliderLabel.getWidth() + 10, 20);
}
void AdsrFront::setSliderParams(juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
