/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ClassSynthAudioProcessor::ClassSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

ClassSynthAudioProcessor::~ClassSynthAudioProcessor()
{

}

//==============================================================================
const juce::String ClassSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ClassSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ClassSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ClassSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ClassSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ClassSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ClassSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ClassSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ClassSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void ClassSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ClassSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++) 
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    filter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void ClassSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ClassSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ClassSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& oscWaveType = *apvts.getRawParameterValue("OSC");

            auto& fmFreq = *apvts.getRawParameterValue("FMFREQ");
            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            voice->getOscilator().setWaveType(oscWaveType);
            voice->getOscilator().setFmParams(fmFreq, fmDepth);
            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
        }
    }
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    auto& filterType = *apvts.getRawParameterValue("FILTER");
    auto& cutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
    auto& resonance = *apvts.getRawParameterValue("FILTERRES");

    filter.updateParameters(filterType, cutoff, resonance);

    filter.process(buffer);
}

//==============================================================================
bool ClassSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ClassSynthAudioProcessor::createEditor()
{
    return new ClassSynthAudioProcessorEditor (*this);
}

//==============================================================================
void ClassSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ClassSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ClassSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout ClassSynthAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //Oscillator and Frequency Modulator
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{ "Sine", "Saw",
        "Square", "Triangle"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ", "FM Frequency", juce::NormalisableRange<float>
    {0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMDEPTH", "FM Depth", juce::NormalisableRange<float>
    {0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));

    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>
        {0.1f, 1.0f, 0.1f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>
        {0.1f, 1.0f, 0.1f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>
        {0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>
        {0.1f, 3.0f, 0.1f }, 0.4f));

    //Filter

    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTER", "Filter", juce::StringArray{ "LowPass", "HighPass",
        "BandPass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float>
    {20.0f, 20000.0f, 0.1f, 0.6f}, 200.0f));    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonace", juce::NormalisableRange<float>
    {1.0f, 10.0f, 0.1f}, 1.0f));
    

    return{ params.begin(),params.end() };
}