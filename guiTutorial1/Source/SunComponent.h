/*
  ==============================================================================

    SunComponent.h
    Created: 14 Jul 2018 7:34:47pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SunComponent    : public Component
{
public:
    SunComponent();
    ~SunComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SunComponent)
};
