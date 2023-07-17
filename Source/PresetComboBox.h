#pragma once
#include <JuceHeader.h>
#include "HayesPitchShifterAudioProcessor.h"

class PresetBar;

class PresetComboBox : public juce::ComboBox
{
public:
    PresetComboBox(HayesPitchShifterAudioProcessor& p, PresetBar* bar);
    void mouseDown(const juce::MouseEvent& event) override;
    void savePreset();
    void loadPreset();
    void deletePreset();

    HayesPitchShifterAudioProcessor& processor;
    PresetBar* presetBar;
    juce::PopupMenu saveLoadMenu;
};
