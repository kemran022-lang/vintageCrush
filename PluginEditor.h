#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class VintageCrushAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    explicit VintageCrushAudioProcessorEditor(VintageCrushAudioProcessor&);
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    VintageCrushAudioProcessor& processor;
    std::array<std::unique_ptr<juce::Slider>, 7> knobs;
    std::array<std::unique_ptr<juce::Label>, 7> labels;
    std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>, 7> attachments;
    juce::TextButton randomButton { "RANDOM" };
    juce::ToggleButton vintageButton { "ANALOG / VINTAGE" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> vintageAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VintageCrushAudioProcessorEditor)
};
