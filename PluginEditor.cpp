#include "PluginEditor.h"

VintageCrushAudioProcessorEditor::VintageCrushAudioProcessorEditor(VintageCrushAudioProcessor& p)
: AudioProcessorEditor(&p), processor(p) {
    setSize(620, 330);
    const std::array<const char*,7> ids { "warm","crunch","vinyl","noise","tone","mix","output" };
    const std::array<const char*,7> names { "WARM","CRUNCH","VINYL","NOISE","TONE","MIX","OUTPUT" };
    for (size_t i=0;i<knobs.size();++i) {
        knobs[i] = std::make_unique<juce::Slider>();
        knobs[i]->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        knobs[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 58, 18);
        addAndMakeVisible(*knobs[i]);
        labels[i] = std::make_unique<juce::Label>();
        labels[i]->setText(names[i], juce::dontSendNotification);
        labels[i]->setJustificationType(juce::Justification::centred);
        addAndMakeVisible(*labels[i]);
        attachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.state, ids[i], *knobs[i]);
    }
    vintageAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processor.state, "vintage", vintageButton);
    addAndMakeVisible(vintageButton);
    addAndMakeVisible(randomButton);
    randomButton.onClick = [this] {
        juce::Random r;
        for (auto id : { "warm","crunch","vinyl","noise","tone","mix","output" })
            processor.state.getParameter(id)->setValueNotifyingHost(r.nextFloat());
    };
}
void VintageCrushAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour(0xff171716));
    g.setColour(juce::Colour(0xffd2a66b));
    g.setFont(juce::Font(juce::FontOptions(25.0f, juce::Font::bold)));
    g.drawText("VINTAGE CRUSH", 18, 12, getWidth()-36, 34, juce::Justification::centred);
    g.setColour(juce::Colour(0xff8b8174));
    g.drawText("WARM SATURATION  •  DIRTY CRUNCH  •  VINYL TEXTURE", 10, 45, getWidth()-20, 20, juce::Justification::centred);
}
void VintageCrushAudioProcessorEditor::resized() {
    const int w = 82, gap = 5, start = 17, top = 90;
    for (int i=0;i<7;++i) {
        int x = start + i*(w+gap);
        labels[i]->setBounds(x, top, w, 22);
        knobs[i]->setBounds(x, top+22, w, 100);
    }
    vintageButton.setBounds(105, 250, 190, 30);
    randomButton.setBounds(345, 250, 150, 30);
}
