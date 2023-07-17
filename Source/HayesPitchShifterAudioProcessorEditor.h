#pragma once

#include "HayesPitchShifterAudioProcessor.h"
#include "CustomLookAndFeel.h"
#include "PitchSlider.h"

class HayesPitchShifterAudioProcessorEditor  : public juce::AudioProcessorEditor
                                             , public juce::TextButton::Listener
{
public:
    HayesPitchShifterAudioProcessorEditor (HayesPitchShifterAudioProcessor* procesor);
    ~HayesPitchShifterAudioProcessorEditor();

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    HayesPitchShifterAudioProcessor* processor;
	PitchSlider pitchSlider;
    juce::Label pitchLabel;
    juce::TextButton pitchModeButton;
    
    juce::Image image;
	
	CustomLookAndFeel customLookAndFeel;

	juce::AudioProcessorValueTreeState::SliderAttachment pitchAttachment;
    juce::AudioProcessorValueTreeState::ButtonAttachment buttonAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesPitchShifterAudioProcessorEditor)
};