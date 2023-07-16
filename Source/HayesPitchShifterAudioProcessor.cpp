#include "HayesPitchShifterAudioProcessor.h"
#include "HayesPitchShifterAudioProcessorEditor.h"

HayesPitchShifterAudioProcessor::HayesPitchShifterAudioProcessor() 
:   apvts { *this, nullptr, "Params", {
            std::make_unique<juce::AudioParameterFloat>("pitch", "Pitch Multiplier",
                juce::NormalisableRange<float>(0.5f, 2.f), 1.0f)
          } }
{
    const auto window = pitchShifter.getLatencyInSamples();
    pitchParam = apvts.getRawParameterValue("pitch");
    setLatencySamples(window);
}

void HayesPitchShifterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{ 
}

void HayesPitchShifterAudioProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiMessages)
{
    const auto numSamples = buffer.getNumSamples();
    const auto totalNumInputChannels = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Need 2 input and output channels at least, further channels will be ignored
    jassert(totalNumInputChannels >= 2);
    jassert(totalNumOutputChannels >= 2);

    // Clear unused output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, numSamples);

    pitchShifter.setPitchRatio(pitchParam->load()); // Set the pitch, rate, and intensity in the PitchShifter
    pitchShifter.process(buffer.getWritePointer(0), numSamples); // Process the block with the PitchShifter
    buffer.copyFrom(1, 0, buffer.getWritePointer(0), numSamples);
}


juce::AudioProcessorEditor* HayesPitchShifterAudioProcessor::createEditor()
{
    return new HayesPitchShifterAudioProcessorEditor(this);
}

void HayesPitchShifterAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto xml = apvts.state.createXml())
        copyXmlToBinary(*xml, destData);
}

void HayesPitchShifterAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        if (xml->hasTagName(apvts.state.getType()))
            apvts.state = juce::ValueTree::fromXml(*xml);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HayesPitchShifterAudioProcessor();
}