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
class OrionaudioAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor&);
    ~OrionaudioAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
 
    std::unique_ptr<AudioFormatReaderSource> playSource;
private:
    
    OrionaudioAudioProcessor& processor;
    enum TransportState
    {
        Stopped,
        Starting,
        Stopping
    };
    
    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void transportStateChanged(TransportState newState);
    
    
    TransportState state;
    
    TextButton openButton;
    TextButton playButton;
    TextButton stopButton;
    AudioFormatManager formatManager;
   
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionaudioAudioProcessorEditor)
};
