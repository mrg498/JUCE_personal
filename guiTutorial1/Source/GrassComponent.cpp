/*
  ==============================================================================

    GrassComponent.cpp
    Created: 14 Jul 2018 6:52:20pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GrassComponent.h"

//==============================================================================
GrassComponent::GrassComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

GrassComponent::~GrassComponent()
{
}

void GrassComponent::paint (Graphics& g)
{
    g.setColour(Colours::green);
    g.drawLine(10, 355, getWidth()-10, 355, 10.0f);
}

void GrassComponent::resized()
{
    
}
