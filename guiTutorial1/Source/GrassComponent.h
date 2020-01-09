/*
  ==============================================================================

    GrassComponent.h
    Created: 14 Jul 2018 6:52:20pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class GrassComponent    : public Component
{
public:
    GrassComponent();
    ~GrassComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrassComponent)
};
