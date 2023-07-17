#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel() 
{
    setColour(juce::Slider::thumbColourId, juce::Colours::darkmagenta);
    setColour(juce::ComboBox::textColourId, juce::Colours::white);
    setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::white);
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, 
                                         const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) 
{
    double radius  = juce::jmin(width / 2, height / 2) - 4.0f;
    double centreX = x + width * 0.5f;
    double centreY = y + height * 0.5f;
    double rx = centreX - radius;
    double ry = centreY - radius;
    double rw = radius * 2.0f;
    double angle = static_cast<double>(rotaryStartAngle) + sliderPos * static_cast<double>(rotaryEndAngle - rotaryStartAngle);
    
    g.setColour(juce::Colours::whitesmoke);
    g.setOpacity(0.33f);
    g.fillEllipse(rx, ry, rw, rw);
  
    g.setColour(juce::Colours::bisque);
    g.setOpacity(1.0f);
    g.drawEllipse(rx, ry, rw, rw, 2.0f);
  
    juce::Path p;
    double pointerLength = radius * 0.5f;
    double pointerThickness = 5.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY)); //animate
    g.setColour(juce::Colours::seashell);
    g.fillPath(p);
}

void CustomLookAndFeel::drawComboBox(juce::Graphics& g, int w, int h, bool isDown, int bx, int by, 
                              int bw, int bh, juce::ComboBox& cb) 
{
    juce::Colour c(30, 8, 33);
    g.setColour(c);
    g.fillAll();
}

juce::Font CustomLookAndFeel::getComboBoxFont(juce::ComboBox & c) 
{
    return getCommonMenuFont(scale);
}

juce::Font CustomLookAndFeel::getPopupMenuFont() 
{
    return getCommonMenuFont(scale);
}

juce::Font CustomLookAndFeel::getCommonMenuFont(float s) 
{
    return juce::Font("Lucida Console", 10.f * s, juce::Font::bold);
}

void CustomLookAndFeel::drawPopupMenuBackground(juce::Graphics& g, int width, int height) 
{
   juce::Colour c(30, 8, 33);
    g.setColour(c);
    g.fillAll();
}

void CustomLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                                              bool isMouseOverButton, bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 4;

    buttonArea.removeFromLeft (edge);
    buttonArea.removeFromTop (edge);

    // background
    g.setColour (juce::Colours::darkorange.withAlpha(button.getToggleState() ? 0.9f : 0.5f));
    g.fillRoundedRectangle (buttonArea.toFloat(), edge);

    // highlight
    if (isMouseOverButton)
    {
        g.setColour (juce::Colours::lightblue.withAlpha (button.getToggleState() ? 0.5f : 0.3f));
        g.drawRoundedRectangle (buttonArea.toFloat(), edge, 1.0f);
    }
}

void CustomLookAndFeel::drawButtonText (juce::Graphics& g, juce::TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    juce::Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    g.setColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                                            : juce::TextButton::textColourOffId)
                       .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    const int yIndent = button.proportionOfHeight (0.35f);
    const int cornerSize = juce::jmin (button.getHeight(), button.getWidth()) / 2;

    const int fontHeight = juce::roundToInt (font.getHeight() * 0.6f);
    const int leftIndent = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    const int textWidth = button.getWidth() - leftIndent - rightIndent;

    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                          juce::Justification::centred, 2);
}

juce::Font CustomLookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
{
    return getCommonMenuFont(scale);
}
