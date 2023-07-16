#pragma once

#include "HayesPitchShifterAudioProcessor.h"
#include "CustomLookAndFeel.h"
#include "PitchSlider.h"

class HayesPitchShifterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HayesPitchShifterAudioProcessorEditor (HayesPitchShifterAudioProcessor* procesor);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    HayesPitchShifterAudioProcessor* processor;
	PitchSlider pitchSlider;
    juce::Label pitchLabel;
    
    juce::Image image;
	
	CustomLookAndFeel customLookAndFeel;

	juce::AudioProcessorValueTreeState::SliderAttachment pitchAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesPitchShifterAudioProcessorEditor)
};