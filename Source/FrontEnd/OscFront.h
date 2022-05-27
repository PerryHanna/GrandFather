/*
  ==============================================================================

    OscFront.h
    Created: 25 May 2022 6:54:52pm
    Author:  Илья

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscFront  : public juce::Component
{
public:
    OscFront(juce::AudioProcessorValueTreeState& apvts,juce::String waveSelectId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscFront() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectAttachment;

    juce::Slider fmFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqSliderAttachment;
    juce::Label fmFreqLabel{ "FM Freq", "FM Freq" };

    juce::Slider fmDepthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthSliderAttachment;
    juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };

    void setSliderParams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscFront)
};
