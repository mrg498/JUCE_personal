/*
  ==============================================================================

    RoofComponent.h
    Created: 14 Jul 2018 7:03:50pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class RoofComponent    : public Component
{
public:
    RoofComponent();
    ~RoofComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoofComponent)
};
