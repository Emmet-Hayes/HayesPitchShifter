#pragma once
#include "../../Common/BaseAudioProcessorEditor.h"
#include "../../Common/CustomLookAndFeel.h"
#include "../../Common/PitchSlider.h"
#include "../../Common/PresetBar.h"
#include "HayesPitchShifterAudioProcessor.h"


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

    juce::Image image;
    CustomLookAndFeel customLookAndFeel;

    PresetBar presetBar;

    PitchSlider pitchSlider;
    juce::Label pitchLabel;
    juce::TextButton pitchModeButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesPitchShifterAudioProcessorEditor)
};
