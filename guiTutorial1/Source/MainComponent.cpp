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
    addAndMakeVisible(wall);
    addAndMakeVisible(grass);
    addAndMakeVisible(roof);
    addAndMakeVisible(sun);
    addAndMakeVisible(text);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll(Colours::skyblue);
}

void MainComponent::resized()
{
    wall.setBounds(getLocalBounds());
    grass.setBounds(getLocalBounds());
    roof.setBounds(getLocalBounds());
    sun.setBounds(getLocalBounds());
    text.setBounds(getLocalBounds());
}
