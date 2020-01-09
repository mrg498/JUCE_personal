/*
  ==============================================================================

    SunComponent.cpp
    Created: 14 Jul 2018 7:34:47pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SunComponent.h"

//==============================================================================
SunComponent::SunComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SunComponent::~SunComponent()
{
}

void SunComponent::paint (Graphics& g)
{
    g.setColour(Colours::yellow);
    g.drawEllipse(100.0f, 50.0f, 50.0f, 50.0f, 2.0f);
    
}

void SunComponent::resized()
{
   

}
