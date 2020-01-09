/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginAudioProcessorEditor::DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (420, 300);
    
    
    delayGain.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    feedBackGain.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    outputGain.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    delay.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    
    delayGain.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 25);
    feedBackGain.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 25);
    outputGain.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 25);
    delay.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 25);

    
    
    delayGain.setRange(0.0, 1.0, 0.01);
    feedBackGain.setRange(0.0, 1.0, 0.01);
    outputGain.setRange(0.0, 1.0,0.01);
    delay.setRange(0.0, 2000.0, 1.0);
    
    delayGain.setValue(0.5);
    feedBackGain.setValue(0.5);
    outputGain.setValue(1.0);
    delay.setValue(1000.0);
    
    
    delay.setTextValueSuffix(" ms");
    delayLabel.setFont(Font ("Comic Sans MS", 20.0f, Font::italic));
    delayLabel.setText("Delay Time", dontSendNotification);
    delayLabel.attachToComponent(&delay, false);
    
    //delayGainLabel.setTextValueSuffix(" ms");
    delayGainLabel.setFont(Font ("Comic Sans MS", 20.0f, Font::italic));
    delayGainLabel.setText("Echo Gain", dontSendNotification);
    delayGainLabel.attachToComponent(&delayGain, false);
    
    feedBackGainLabel.setFont(Font ("Comic Sans MS", 20.0f, Font::italic));
    feedBackGainLabel.setText("Feedback", dontSendNotification);
    feedBackGainLabel.attachToComponent(&feedBackGain, false);
    
    outputGainLabel.setFont(Font ("Comic Sans MS", 20.0f, Font::italic));
    outputGainLabel.setText("Wet/Dry", dontSendNotification);
    outputGainLabel.attachToComponent(&outputGain, false);
    
    
    delayGain.addListener(this);
    feedBackGain.addListener(this);
    outputGain.addListener(this);
    delay.addListener(this);
    
    addAndMakeVisible(delayGain);
    addAndMakeVisible(feedBackGain);
    addAndMakeVisible(outputGain);
    addAndMakeVisible(delay);

    
}

DelayPluginAudioProcessorEditor::~DelayPluginAudioProcessorEditor()
{
}

//==============================================================================
void DelayPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::darkred);
    
    g.setColour (Colours::darkgrey);
    
    auto centralArea = getLocalBounds().toFloat().reduced (1.0f);
    g.drawRoundedRectangle(centralArea, 10.0f, 8.0f);
    
    
    
    
}

void DelayPluginAudioProcessorEditor::resized()
{
    delayGain.setBounds(30, 50, 100, 100);
    feedBackGain.setBounds(150, 50, 100, 100);
    outputGain.setBounds(270, 50, 100, 100);
    delay.setBounds(50, 200, 300, 50);
}

void DelayPluginAudioProcessorEditor::sliderValueChanged(Slider *dial)
{
    if(dial == &delayGain)
    {
        processor.delayBufGain = delayGain.getValue();
    }
    else if(dial == &feedBackGain)
    {
        processor.feedBackGain = feedBackGain.getValue();
    }
    else if(dial == &outputGain)
    {
        processor.outputGain = outputGain.getValue();
    }
    else if(dial == &delay)
    {
        processor.delay = delay.getValue();
    }
    
    
}
