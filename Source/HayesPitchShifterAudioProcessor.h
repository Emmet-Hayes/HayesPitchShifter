#pragma once
#include <JuceHeader.h>
#include <atomic>

#include "../DSP/PhaseVocoder.h"
#include "../DSP/PitchShifter.h"
#include "../DSP/PeakShifter.h"
#include "../../Common/BaseAudioProcessor.h"

class HayesPitchShifterAudioProcessor  : public BaseAudioProcessor
{
public:
    HayesPitchShifterAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
    juce::AudioProcessorEditor* createEditor() override;
  
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() override;

private:
    float calculateDiscretePitchRatio();

    PitchShifter pitchShifterL;
    PitchShifter pitchShifterR;
    std::atomic<float>* pitchParam = nullptr;
    std::atomic<float>* discreteParam = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesPitchShifterAudioProcessor)
};
