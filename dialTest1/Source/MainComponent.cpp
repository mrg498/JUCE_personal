/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    dial1.setSliderStyle(Slider::SliderStyle::Rotary);
    dial1.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(dial1);
    
    dial2.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    dial2.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(dial2);
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll(Colours::silver);
    
}

void MainComponent::resized()
{
    const int border = 50;
    Rectangle<int> area = getLocalBounds();
    Rectangle<int> dial_area = area.removeFromTop(area.getHeight()/2);
    dial1.setBounds(dial_area.removeFromLeft(area.getWidth()/2).reduced(border));
    dial2.setBounds(dial_area.removeFromRight(area.getWidth()/2).reduced(border));
}
