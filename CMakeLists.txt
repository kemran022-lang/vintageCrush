cmake_minimum_required(VERSION 3.22)
project(VintageCrush VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(
  JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 8.0.6
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(VintageCrush
    COMPANY_NAME "Vintage Audio Lab"
    BUNDLE_ID "com.vintageaudiolab.vintagecrush"
    PLUGIN_MANUFACTURER_CODE VnAu
    PLUGIN_CODE VnCr
    FORMATS VST3
    PRODUCT_NAME "Vintage Crush"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
)

target_sources(VintageCrush PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)
target_compile_features(VintageCrush PRIVATE cxx_std_17)
target_link_libraries(VintageCrush PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
