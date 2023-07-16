#pragma once
#include <JuceHeader.h>

class PitchSlider : public juce::Slider
{
public:
    PitchSlider() : juce::Slider() {}

    juce::String getTextFromValue(double value) override
    {
        return juce::String(value * 100, 1) + "%";
    }
};

