#include "HayesPitchShifterAudioProcessor.h"
#include "HayesPitchShifterAudioProcessorEditor.h"

HayesPitchShifterAudioProcessorEditor::HayesPitchShifterAudioProcessorEditor (HayesPitchShifterAudioProcessor& p)
:   BaseAudioProcessorEditor { p }
,   processor              { p }
,   presetBar              { p }
{
    presetBar.setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible(presetBar);

    pitchLabel.setLookAndFeel(&customLookAndFeel);
    pitchLabel.setFont(customLookAndFeel.getPopupMenuFont());
    pitchLabel.setText("Pitch", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(pitchLabel);

    pitchSlider.setLookAndFeel(&customLookAndFeel);
    pitchSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (pitchSlider);

    pitchModeButton.setLookAndFeel(&customLookAndFeel);
    pitchModeButton.setButtonText("Intervals");
    pitchModeButton.setToggleable(true);
    pitchModeButton.setToggleState(true, juce::dontSendNotification);
    pitchModeButton.addListener(this);
    addAndMakeVisible(pitchModeButton);

    image = juce::ImageCache::getFromMemory(BinaryData::bg_file_jpg, BinaryData::bg_file_jpgSize);
    
    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (p.apvts, "pitch", pitchSlider);
    buttonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.apvts, "discrete", pitchModeButton);

    setSize (200, 150);
}

HayesPitchShifterAudioProcessorEditor::~HayesPitchShifterAudioProcessorEditor()
{
    pitchModeButton.removeListener(this);
}

void HayesPitchShifterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(image, 0, 0, 200, 150, 0, 0, 800, 600);
}

void HayesPitchShifterAudioProcessorEditor::resized()
{
    presetBar.setBounds(0, 0, 200, 20);
    pitchLabel.setBounds(77, 20, 100, 30);
    pitchSlider.setBounds(57, 40, 80, 80);
    pitchModeButton.setBounds(55, 125, 80, 20);
}

void HayesPitchShifterAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &pitchModeButton)
    {
        pitchSlider.changePitchMode();
        pitchModeButton.setToggleState(!pitchModeButton.getToggleState(), juce::dontSendNotification);
    }
}
