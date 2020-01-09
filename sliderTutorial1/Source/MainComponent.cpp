/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    
    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50, 5000);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.addListener(this);
    
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);
    
    addAndMakeVisible(durationSlider);
    durationSlider.setRange(1.0/frequencySlider.getMaximum(), 1.0/frequencySlider.getMinimum());
    durationSlider.setTextValueSuffix(" sec");
    durationSlider.addListener(this);
    
    addAndMakeVisible(durationLabel);
    durationLabel.setText("Duration", dontSendNotification);
    durationLabel.attachToComponent(&durationSlider, true);
    
    frequencySlider.setValue(5000.0);
    frequencySlider.setSkewFactorFromMidPoint(500.0);
    durationSlider.setSkewFactorFromMidPoint(1.0/500);
    
    frequencySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 120, frequencySlider.getTextBoxHeight());
    durationSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 120, frequencySlider.getTextBoxHeight());
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    
}

void MainComponent::resized()
{
    const int border = 120;
    frequencySlider.setBounds(border, 20, getWidth()-border, 20);
    durationSlider.setBounds(border, 40, getWidth()-border, 40);
}
