#include "PluginProcessor.h"
#include "PluginEditor.h"

VintageCrushAudioProcessor::VintageCrushAudioProcessor()
: AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                  .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
  state(*this, nullptr, "PARAMETERS", createParams()) {}

juce::AudioProcessorValueTreeState::ParameterLayout VintageCrushAudioProcessor::createParams() {
    using P = juce::AudioParameterFloat;
    juce::AudioProcessorValueTreeState::ParameterLayout p;
    auto add = [&p](const char* id, const char* name, float def) {
        p.add(std::make_unique<P>(id, name, juce::NormalisableRange<float>(0.0f, 1.0f), def));
    };
    add("warm", "Warm", 0.25f); add("crunch", "Crunch", 0.15f);
    add("vinyl", "Vinyl", 0.15f); add("noise", "Noise", 0.08f);
    add("tone", "Tone", 0.55f); add("mix", "Mix", 1.0f);
    add("output", "Output", 0.75f);
    p.add(std::make_unique<juce::AudioParameterBool>("vintage", "Analog / Vintage", true));
    return p;
}
void VintageCrushAudioProcessor::prepareToPlay(double, int) {}
bool VintageCrushAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const {
    return l.getMainInputChannelSet() == l.getMainOutputChannelSet()
        && (l.getMainOutputChannelSet() == juce::AudioChannelSet::mono()
         || l.getMainOutputChannelSet() == juce::AudioChannelSet::stereo());
}
void VintageCrushAudioProcessor::processBlock(juce::AudioBuffer<float>& b, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    auto* warm = state.getRawParameterValue("warm");
    auto* crunch = state.getRawParameterValue("crunch");
    auto* vinyl = state.getRawParameterValue("vinyl");
    auto* noise = state.getRawParameterValue("noise");
    auto* tone = state.getRawParameterValue("tone");
    auto* mix = state.getRawParameterValue("mix");
    auto* output = state.getRawParameterValue("output");
    const bool vintage = state.getRawParameterValue("vintage")->load() > 0.5f;
    for (int ch = 0; ch < b.getNumChannels(); ++ch) {
        auto* x = b.getWritePointer(ch);
        for (int i = 0; i < b.getNumSamples(); ++i) {
            float dry = x[i], y = dry;
            float drive = 1.0f + warm->load() * (vintage ? 5.0f : 3.0f);
            y = std::tanh(y * drive) / std::tanh(drive);
            float hard = 1.0f + crunch->load() * 18.0f;
            float crushed = std::tanh(y * hard);
            y += (crushed - y) * crunch->load();
            float tilt = 0.65f + tone->load() * 0.7f;
            y *= tilt;
            if (noise->load() > 0.001f || vinyl->load() > 0.001f) {
                float n = (random.nextFloat() * 2.0f - 1.0f) * noise->load() * 0.025f;
                float crackle = (random.nextFloat() > 0.9995f ? (random.nextFloat()*2.0f-1.0f) : 0.0f) * vinyl->load() * 0.18f;
                y += n + crackle;
            }
            x[i] = (dry + (y - dry) * mix->load()) * output->load();
        }
    }
}
juce::AudioProcessorEditor* VintageCrushAudioProcessor::createEditor() { return new VintageCrushAudioProcessorEditor(*this); }
void VintageCrushAudioProcessor::getStateInformation(juce::MemoryBlock& d) { auto s = state.copyState(); std::unique_ptr<juce::XmlElement> x(s.createXml()); copyXmlToBinary(*x, d); }
void VintageCrushAudioProcessor::setStateInformation(const void* d, int n) { std::unique_ptr<juce::XmlElement> x(getXmlFromBinary(d,n)); if (x && x->hasTagName(state.state.getType())) state.replaceState(juce::ValueTree::fromXml(*x)); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new VintageCrushAudioProcessor(); }
