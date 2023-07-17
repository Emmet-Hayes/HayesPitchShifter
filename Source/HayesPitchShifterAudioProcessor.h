#pragma once
#include <JuceHeader.h>
#include <atomic>

#include "../DSP/PhaseVocoder.h"
#include "../DSP/PitchShifter.h"
#include "../DSP/PeakShifter.h"

class HayesPitchShifterAudioProcessor  : public juce::AudioProcessor
{
public:
    HayesPitchShifterAudioProcessor();

    void releaseResources() override {}
    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int /*index*/) override {}
    const juce::String getProgramName(int /*index*/) override { return {}; }
    void changeProgramName(int /*index*/, const juce::String& /*newName*/) override {}
    bool hasEditor() const override { return true; }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
    juce::AudioProcessorEditor* createEditor() override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

private:
    float calculateDiscretePitchRatio();

	PitchShifter pitchShifter;
	std::atomic<float>* pitchParam = nullptr;
	std::atomic<float>* discreteParam = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesPitchShifterAudioProcessor)
};