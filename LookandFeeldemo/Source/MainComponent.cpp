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
    
    addAndMakeVisible(dial1);
    dial1.setSliderStyle(Slider::SliderStyle::Rotary);
    dial1.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    
    
    
    addAndMakeVisible(dial2);
    dial2.setSliderStyle(Slider::SliderStyle::Rotary);
    dial2.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    
    dial2.setLookAndFeel(&otherLookandFeel);
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
    const int border = 20;
    const int dialWidth = getWidth()/2 - border;
    const int dialHeight = getHeight() - 100 - border;
    dial1.setBounds(border, border, dialWidth, dialHeight);
    dial2.setBounds(getWidth()/2, border, dialWidth, dialHeight);
}
