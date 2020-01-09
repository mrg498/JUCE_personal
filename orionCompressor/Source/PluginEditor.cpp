/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OrionCompressorAudioProcessorEditor::OrionCompressorAudioProcessorEditor (OrionCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)

{
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 1000);
    
    addAndMakeVisible(buttonONOFF);
    buttonONOFF.setButtonText("On/Off");
    buttonONOFF.addListener(this);
    buttonONOFF.setColour(TextButton::buttonColourId, Colours::black);
    buttonONOFF.setColour(TextButton::buttonOnColourId, Colours::blue);
    
    buttonONOFF.setClickingTogglesState(true);

    
    addAndMakeVisible(sliderThreshold);
    sliderThreshold.setRange(-60.0, 0);
    sliderThreshold.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderThreshold.setTextValueSuffix("dB");
    sliderThreshold.addListener(this);
    
    addAndMakeVisible(sliderThresholdLabel);
    sliderThresholdLabel.setText("Threshold", dontSendNotification);
    sliderThresholdLabel.attachToComponent(&sliderThreshold, true);
    
    
    addAndMakeVisible(sliderRatio);
    sliderRatio.setRange(1.0, 100.0, 0.1);
    sliderRatio.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderRatio.setTextValueSuffix("dB");
    sliderRatio.addListener(this);
    
    addAndMakeVisible(sliderRatioLabel);
    sliderRatioLabel.setText("Ratio", dontSendNotification);
    sliderRatioLabel.attachToComponent(&sliderRatio, true);
    
   
    
    addAndMakeVisible(sliderGain);
    sliderGain.setRange(0.0, 40.0, 1.0);
    sliderGain.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderGain.setTextValueSuffix("dB");
    sliderGain.addListener(this);
    
    addAndMakeVisible(sliderGainLabel);
    sliderGainLabel.setText("Makeup Gain", dontSendNotification);
    sliderGainLabel.attachToComponent(&sliderGain, true);
    
    addAndMakeVisible(sliderAttack);
    sliderAttack.setRange(0.1, 80.0, 0.1);
    sliderAttack.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderAttack.setTextValueSuffix("ms");
    sliderAttack.addListener(this);
    
    addAndMakeVisible(sliderAttackLabel);
    sliderAttackLabel.setText("Attack", dontSendNotification);
    sliderAttackLabel.attachToComponent(&sliderAttack, true);
    
    addAndMakeVisible(sliderRelease);
    sliderRelease.setRange(0.1, 1000.0, 0.1);
    sliderRelease.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderRelease.setTextValueSuffix("ms");
    sliderRelease.addListener(this);
    
    addAndMakeVisible(sliderReleaseLabel);
    sliderReleaseLabel.setText("Release", dontSendNotification);
    sliderReleaseLabel.attachToComponent(&sliderRelease, true);
    
    
    startTimer(50);
    
}

OrionCompressorAudioProcessorEditor::~OrionCompressorAudioProcessorEditor()
{
    
}

//==============================================================================
void OrionCompressorAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::tan);
    
}

void OrionCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    buttonONOFF.setBounds(50, 50, 200, 200);
    
    sliderGain.setBounds(50, 300, 200, 200);
    
    sliderRatio.setBounds(50, 500, 200, 200);
    
    sliderAttack.setBounds(300, 50, 200, 200);
    
    sliderRelease.setBounds(600, 50, 200, 200);
}

void OrionCompressorAudioProcessorEditor::buttonClicked(Button *buttonThatWasClicked)
{
    if(buttonThatWasClicked == &buttonONOFF)
    {
        processor.compressorONOFF = buttonONOFF.getToggleState();
        
    }
    
}

void OrionCompressorAudioProcessorEditor::sliderValueChanged(Slider *sliderThatWasMoved)
{
    if(sliderThatWasMoved == &sliderThreshold)
    {
        processor.setThreshold(sliderThreshold.getValue());
    }
    
    else if(sliderThatWasMoved == &sliderGain)
    {
        processor.setGain(sliderGain.getValue());
    }
    
    else if(sliderThatWasMoved == &sliderRatio)
    {
        processor.setRatio(sliderRatio.getValue());
    }
    
    else if(sliderThatWasMoved == &sliderAttack)
    {
        processor.setAttackTime(sliderAttack.getValue());
    }
    
    else if(sliderThatWasMoved == &sliderRelease)
    {
        processor.setReleaseTime(sliderRelease.getValue());
    }
}

void OrionCompressorAudioProcessorEditor::timerCallback()
{
    
    // Display the ON/OFF button in its correct state
    if (buttonONOFF.getToggleState()) buttonONOFF.setToggleState(true, dontSendNotification);
    else buttonONOFF.setToggleState(false, dontSendNotification);
}
