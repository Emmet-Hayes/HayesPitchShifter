#pragma once
#include <JuceHeader.h>
#include <unordered_map>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	void drawRotarySlider(juce::Graphics&, int, int, int, int, float, const float,
		const float, juce::Slider&) override;
	void drawComboBox(juce::Graphics&, int, int, bool, int, int, int, int, juce::ComboBox&) override;
	juce::Font getComboBoxFont(juce::ComboBox&) override;
	juce::Font getPopupMenuFont() override;
	void drawPopupMenuBackground(juce::Graphics&, int, int) override;
	inline void setScale(const float s) { scale = s; }
	juce::Font getCommonMenuFont(float);
    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown);

    void drawButtonText(juce::Graphics& g, juce::TextButton& button, 
                        bool /*isMouseOverButton*/, bool /*isButtonDown*/);
	juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight);
private:
	float scale = 1.0f;
	float rotaryOutlineBrightness = 1.0f;

};
