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
class OrionCompressorAudioProcessorEditor  : public AudioProcessorEditor,

                                             public Slider::Listener,
                                             public Button::Listener,
                                             public Timer
{
public:
    OrionCompressorAudioProcessorEditor (OrionCompressorAudioProcessor&);
    ~OrionCompressorAudioProcessorEditor();

    //==============================================================================
    void timerCallback() override;
    
    
    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OrionCompressorAudioProcessor& processor;

    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;
    
    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;
    
    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);
    
    TextButton buttonONOFF;
    
    Slider sliderThreshold;
    Label sliderThresholdLabel;
    
    Slider sliderRatio;
    Label sliderRatioLabel;
    
    Slider sliderGain;
    Label sliderGainLabel;
    
    Slider sliderAttack;
    Label sliderAttackLabel;
    
    Slider sliderRelease;
    Label sliderReleaseLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionCompressorAudioProcessorEditor)
};
