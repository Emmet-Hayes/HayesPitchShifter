#include "HayesPitchShifterAudioProcessor.h"
#include "HayesPitchShifterAudioProcessorEditor.h"

HayesPitchShifterAudioProcessorEditor::HayesPitchShifterAudioProcessorEditor (HayesPitchShifterAudioProcessor* p)
:	AudioProcessorEditor (*p)
,   processor (p)
,   pitchAttachment { p->apvts, "pitch", pitchSlider }
{
	pitchLabel.setLookAndFeel(&customLookAndFeel);
	pitchLabel.setFont(customLookAndFeel.getCommonMenuFont(1.0));
	pitchLabel.setText("Pitch", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(pitchLabel);

    pitchSlider.setLookAndFeel(&customLookAndFeel);
	pitchSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
	addAndMakeVisible (pitchSlider);

    image = juce::ImageCache::getFromMemory(BinaryData::bg_file_jpg, BinaryData::bg_file_jpgSize);
	setSize (200, 150);
}

void HayesPitchShifterAudioProcessorEditor::paint (juce::Graphics& g)
{
	g.drawImage(image, 0, 0, 200, 150, 250, 150, 400, 300);
}

void HayesPitchShifterAudioProcessorEditor::resized()
{
	pitchLabel.setBounds(75, 5, 100, 30);
	pitchSlider.setBounds(50, 40, 100, 100);
}