/*
  ==============================================================================

    RoofComponent.cpp
    Created: 14 Jul 2018 7:03:50pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "RoofComponent.h"

//==============================================================================
RoofComponent::RoofComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

RoofComponent::~RoofComponent()
{
}

void RoofComponent::paint (Graphics& g)
{
    g.setColour(Colours::red);
    Path p;
    p.startNewSubPath(175, 199);
    p.lineTo(425, 199);
    p.lineTo(300, 100);
    p.closeSubPath();
    
    g.strokePath(p, PathStrokeType(2.0f));
    g.fillPath(p);
}

void RoofComponent::resized()
{
   

}
