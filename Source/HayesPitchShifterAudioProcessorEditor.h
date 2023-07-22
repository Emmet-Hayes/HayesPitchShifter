#pragma once
#include "HayesPitchShifterAudioProcessor.h"
#include "../../Common/BaseAudioProcessorEditor.h"
#include "../../Common/CustomLookAndFeel.h"
#include "../../Common/PitchSlider.h"
#include "../../Common/PresetBar.h"

class HayesPitchShifterAudioProcessorEditor  : public BaseAudioProcessorEditor
                                            , public juce::TextButton::Listener
{
public:
    HayesPitchShifterAudioProcessorEditor (HayesPitchShifterAudioProcessor& procesor);
    ~HayesPitchShifterAudioProcessorEditor();

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    HayesPitchShifterAudioProcessor& processor;
    
    PitchSlider pitchSlider;
    juce::Label pitchLabel;
    juce::TextButton pitchModeButton;
    
    PresetBar presetBar;

    juce::Image image;

    CustomLookAndFeel customLookAndFeel;

    juce::AudioProcessorValueTreeState::SliderAttachment pitchAttachment;
    juce::AudioProcessorValueTreeState::ButtonAttachment buttonAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesPitchShifterAudioProcessorEditor)
};
