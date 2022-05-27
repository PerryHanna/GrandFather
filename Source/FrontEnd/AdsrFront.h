/*
  ==============================================================================

    AdsrFront.h
    Created: 25 May 2022 2:42:58pm
    Author:  Илья

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrFront  : public juce::Component
{
public:
    AdsrFront(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrFront() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider, juce::Label& label);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackSliderLabel{ "A", "A" };
    juce::Label decaySliderLabel{ "D", "D" };
    juce::Label sustainSliderLabel{ "S", "S" };
    juce::Label releaseSliderLabel{ "R", "R" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrFront)
};
