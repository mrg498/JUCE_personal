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
class _14juce_gainSlider1AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    _14juce_gainSlider1AudioProcessorEditor (_14juce_gainSlider1AudioProcessor&);
    ~_14juce_gainSlider1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _14juce_gainSlider1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_14juce_gainSlider1AudioProcessorEditor)
};
