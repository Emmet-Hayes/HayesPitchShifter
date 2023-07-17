#include "HayesPitchShifterAudioProcessor.h"
#include "HayesPitchShifterAudioProcessorEditor.h"

HayesPitchShifterAudioProcessor::HayesPitchShifterAudioProcessor() 
:   apvts { *this, nullptr, "Params", {
            std::make_unique<juce::AudioParameterFloat>("pitch", "Pitch Multiplier",
                juce::NormalisableRange<float>(0.5f, 2.f), 1.0f),
            std::make_unique<juce::AudioParameterBool>("discrete", "Discrete Pitch", false)
          } }
{
    const auto window = pitchShifter.getLatencyInSamples();
    pitchParam = apvts.getRawParameterValue("pitch");
    discreteParam = apvts.getRawParameterValue("discrete");
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

    if (discreteParam->load() > 0.5f)
    {
        float discretePitchRatio = calculateDiscretePitchRatio();
        pitchShifter.setPitchRatio(discretePitchRatio);
    }
    else
        pitchShifter.setPitchRatio(pitchParam->load());
        
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

float HayesPitchShifterAudioProcessor::calculateDiscretePitchRatio()
{
    float rawParamVal = pitchParam->load();
    if (rawParamVal >= 1.943875f)
        return 2.0f; // octave up
    if (rawParamVal >= 1.834775f)
        return 1.88775f; // major seventh
    if (rawParamVal >= 1.731795f)
        return 1.78180f; // minor seventh
    if (rawParamVal >= 1.634595f)
        return 1.68179f; // major sixth
    if (rawParamVal >= 1.542615f)
        return 1.58740f; // minor sixth
    if (rawParamVal >= 1.456075f)
        return 1.49831f; // perfect fifth
    if (rawParamVal >= 1.374525f)
        return 1.41421f; // tritone
    if (rawParamVal >= 1.297725f)
        return 1.33484f; // perfect fourth
    if (rawParamVal >= 1.224945f)
        return 1.25992f; // major third
    if (rawParamVal >= 1.156245f)
        return 1.18921f; // minor third
    if (rawParamVal >= 1.090995f)
        return 1.12246f; // major second
    if (rawParamVal >= 1.028725f)
        return 1.05946f; // minor second
    if (rawParamVal >= 0.973195f)
        return 1.0f; // unison
    if (rawParamVal >= 0.91738f)
        return 0.94387f; // minor second down
    if (rawParamVal >= 0.865895f)
        return 0.89090f; // major second down
    if (rawParamVal >= 0.817295f)
        return 0.84090f; // minor third down
    if (rawParamVal >= 0.771305f)
        return 0.79370f; // major third down
    if (rawParamVal >= 0.72803f)
        return 0.74915f; // perfect fourth down
    if (rawParamVal >= 0.68726f)
        return 0.70711f; // tritone down
    if (rawParamVal >= 0.64886f)
        return 0.66742f; // perfect fifth down
    if (rawParamVal >= 0.61247f)
        return 0.62996f; // minor sixth down
    if (rawParamVal >= 0.57812f)
        return 0.59460f; // major sixth down
    if (rawParamVal >= 0.5455f)
        return 0.56123f; // minor seventh down
    if (rawParamVal >= 0.51436f)
        return 0.52973f; // major seventh down
    return 0.5f; // octave down
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HayesPitchShifterAudioProcessor();
}