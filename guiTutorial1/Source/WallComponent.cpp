/*
  ==============================================================================

    WallComponent.cpp
    Created: 14 Jul 2018 4:53:01pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WallComponent.h"

//==============================================================================
WallComponent::WallComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WallComponent::~WallComponent()
{
}

void WallComponent::paint (Graphics& g)
{
    Rectangle <float> wall(200,200,200,150);
    g.fillCheckerBoard(wall, 20, 10, Colours::brown, Colours::beige);
    g.drawRect(wall);
}

void WallComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
