#include "HayesPitchShifterAudioProcessor.h"
#include "HayesPitchShifterAudioProcessorEditor.h"

HayesPitchShifterAudioProcessorEditor::HayesPitchShifterAudioProcessorEditor(HayesPitchShifterAudioProcessor& p)
:   BaseAudioProcessorEditor { p }
,   processor                { p }
,   presetBar                { p }
{
    setLookAndFeel(&customLookAndFeel);
    
    addAndMakeVisible(presetBar);

    pitchLabel.setFont(customLookAndFeel.getPopupMenuFont());
    pitchLabel.setText("Pitch", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(pitchLabel);

    pitchSlider.setSliderStyle(juce::Slider::Rotary);
    pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(pitchSlider);

    pitchModeButton.setButtonText("Intervals");
    pitchModeButton.setToggleable(true);
    pitchModeButton.setToggleState(true, juce::dontSendNotification);
    pitchModeButton.addListener(this);
    addAndMakeVisible(pitchModeButton);

    image = juce::ImageCache::getFromMemory(BinaryData::bg_file_jpg, BinaryData::bg_file_jpgSize);

    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.apvts, "pitch", pitchSlider);
    buttonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.apvts, "discrete", pitchModeButton);

    const auto ratio = static_cast<double> (defaultWidth) / defaultHeight;
    setResizable(false, true);
    getConstrainer()->setFixedAspectRatio(ratio);
    getConstrainer()->setSizeLimits(defaultWidth, defaultHeight, defaultWidth * 2, defaultHeight * 2);
    setSize(defaultWidth, defaultHeight);
}

HayesPitchShifterAudioProcessorEditor::~HayesPitchShifterAudioProcessorEditor()
{
    pitchModeButton.removeListener(this);
}

void HayesPitchShifterAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.drawImage(image, 0, 0, getWidth(), getHeight(), 0, 0, 800, 600);
}

void HayesPitchShifterAudioProcessorEditor::resized()
{
    const auto scale = static_cast<float> (getWidth()) / defaultWidth;

    auto setBoundsAndApplyScaling = [&](juce::Component* component, int x, int y, int w, int h)
    {
        component->setBounds(static_cast<int>(x * scale), static_cast<int>(y * scale),
            static_cast<int>(w * scale), static_cast<int>(h * scale));
    };
    
    customLookAndFeel.setWindowScale(scale);
    setBoundsAndApplyScaling(&presetBar, 0, 0, 200, 20);
    setBoundsAndApplyScaling(&pitchLabel, 78, 20, 100, 30);
    setBoundsAndApplyScaling(&pitchSlider, 57, 40, 80, 80);
    setBoundsAndApplyScaling(&pitchModeButton, 55, 125, 80, 20);
}

void HayesPitchShifterAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &pitchModeButton)
    {
        pitchSlider.changePitchMode();
        pitchModeButton.setToggleState(!pitchModeButton.getToggleState(), juce::dontSendNotification);
    }
}