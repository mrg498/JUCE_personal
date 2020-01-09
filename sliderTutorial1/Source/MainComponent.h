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
class MainComponent   : public Component, public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider* slider) override
    {
        if (slider == &frequencySlider)
            durationSlider.setValue(1.0/frequencySlider.getValue());
        else if (slider == &durationSlider)
            frequencySlider.setValue(1.0/durationSlider.getValue());
    }

private:
    
    Slider frequencySlider;
    Label frequencyLabel;
    
    Slider durationSlider;
    Label durationLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
