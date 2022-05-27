/*
  ==============================================================================

    FilterFront.h
    Created: 27 May 2022 12:07:18am
    Author:  Илья

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterFront  : public juce::Component
{
public:
    FilterFront(juce::AudioProcessorValueTreeState& apvts, juce::String filterSelectId, juce::String filterCutoffId,
        juce::String filterResonaceId);
    ~FilterFront() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> fillterSelectAttachment;

    juce::Slider filterCutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffSliderAttachment;
    juce::Label filterCutoffLabel{ "Filter Cutoff", "Filter Cutoff" };

    juce::Slider filterResonaceSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonaceSliderAttachment;
    juce::Label filterResonaceLabel{ "Filter Res", "Filter Res" };

    void setSliderParams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterFront)
};
