/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.

*/

class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    OtherLookAndFeel(){
        setColour(Slider::rotarySliderOutlineColourId, Colours::darkorange);
        setColour(Slider::thumbColourId, Colours::whitesmoke);
        setColour(Slider::rotarySliderFillColourId, Colours::turquoise);
    }
    
    
};

class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    Slider dial1;
    Slider dial2;
    
    OtherLookAndFeel otherLookandFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


