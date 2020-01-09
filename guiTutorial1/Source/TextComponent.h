/*
  ==============================================================================

    TextComponent.h
    Created: 14 Jul 2018 7:50:16pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TextComponent    : public Component
{
public:
    TextComponent();
    ~TextComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextComponent)
};
