#include "HayesPitchShifterAudioProcessor.h"
#include "HayesPitchShifterAudioProcessorEditor.h"

HayesPitchShifterAudioProcessorEditor::HayesPitchShifterAudioProcessorEditor (HayesPitchShifterAudioProcessor& p)
:   AudioProcessorEditor { &p }
,   processor            { &p }
,   presetBar            { p }
,   pitchAttachment      { p.apvts, "pitch",    pitchSlider }
,   buttonAttachment     { p.apvts, "discrete", pitchModeButton }
{
	pitchLabel.setLookAndFeel(&customLookAndFeel);
	pitchLabel.setFont(customLookAndFeel.getCommonMenuFont(1.0));
	pitchLabel.setText("Pitch", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(pitchLabel);

    pitchSlider.setLookAndFeel(&customLookAndFeel);
	pitchSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
	addAndMakeVisible (pitchSlider);

	pitchModeButton.setLookAndFeel(&customLookAndFeel);
	pitchModeButton.setButtonText("Intervals");
	pitchModeButton.setToggleable(true);
	pitchModeButton.addListener(this);
	addAndMakeVisible(pitchModeButton);

	presetBar.setLookAndFeel(&customLookAndFeel);
	addAndMakeVisible(presetBar);
	
    image = juce::ImageCache::getFromMemory(BinaryData::bg_file_jpg, BinaryData::bg_file_jpgSize);
	setSize (200, 150);
}

HayesPitchShifterAudioProcessorEditor::~HayesPitchShifterAudioProcessorEditor()
{
	pitchModeButton.removeListener(this);
}

void HayesPitchShifterAudioProcessorEditor::paint (juce::Graphics& g)
{
	g.drawImage(image, 0, 0, 200, 150, 250, 150, 400, 300);
}

void HayesPitchShifterAudioProcessorEditor::resized()
{
	presetBar.setBounds(0, 0, 200, 20);
	pitchLabel.setBounds(75, 20, 100, 30);
	pitchSlider.setBounds(55, 40, 80, 80);
	pitchModeButton.setBounds(55, 125, 80, 20);
}

void HayesPitchShifterAudioProcessorEditor::buttonClicked(juce::Button* button)
{
	if (button == &pitchModeButton)
	{
		pitchModeButton.setToggleState(!pitchModeButton.getToggleState(), juce::dontSendNotification);
		pitchSlider.changePitchMode();
	}
}
