/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DelayPluginAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener

{
public:
    DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor&);
    ~DelayPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *dial) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DelayPluginAudioProcessor& processor;
    
    Slider delayGain;
    Slider feedBackGain;
    Slider outputGain;
    Slider delay;
    
    Label delayLabel;
    Label delayGainLabel;
    Label feedBackGainLabel;
    Label outputGainLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPluginAudioProcessorEditor)
};
