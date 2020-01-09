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
class MainComponent   : public AudioAppComponent,
                        public Slider::Listener
{
public:
    
    void sliderValueChanged(Slider* slider) override
    {
        if(slider == &freq_slider)
        {
            frequency = freq_slider.getValue();
        }
        else if(slider == &amp_slider)
        {
            amplitude = amp_slider.getValue();
        }
    }
    
    void updateFrequency()
    {
        increment = (frequency*wt_size)/currentSampleRate;
        phase = fmod(phase + increment,wt_size);
    }
    
    
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    Slider freq_slider, amp_slider;
    Label freqLabel, ampLabel;
    
    Array<float> waveTable;
    double wt_size;
    double frequency;
    double increment;
    double amplitude;
    double phase, phaseAtBufferStart;
    double currentSampleRate;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
