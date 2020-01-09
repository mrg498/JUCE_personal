/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    freq_slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    freq_slider.setRange(50, 500);
    freq_slider.setTextValueSuffix("Hz");
    freq_slider.addListener(this);
    freq_slider.setValue(250);
    addAndMakeVisible(freq_slider);
    freqLabel.setText("Frequency", dontSendNotification);
    freqLabel.attachToComponent(&freq_slider, true);
    
    amp_slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    amp_slider.setRange(0.0, 1.0);
    
    amp_slider.addListener(this);
    amp_slider.setValue(0.0);
    ampLabel.setText("Amplitude", dontSendNotification);
    ampLabel.attachToComponent(&amp_slider, true);
    
    addAndMakeVisible(amp_slider);
    

    // specify the number of input and output channels that we want to open
    setAudioChannels (2, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    amplitude = amp_slider.getValue();
    frequency = freq_slider.getValue();
    phase = phaseAtBufferStart = 0;
    wt_size = 1024;
    
    currentSampleRate = sampleRate;
    
    // one cycle of a sine wave
    for(int i = 0; i<wt_size;i++)
    {
        waveTable.insert(i, sin((2.0*double_Pi*i)/wt_size));
    }
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    for(int channel = 0; channel<bufferToFill.buffer->getNumChannels(); channel++)
    {
        float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        phase = phaseAtBufferStart;
    
        for(int sample = 0; sample < bufferToFill.numSamples; sample++)
        {
            buffer[sample] = waveTable[(int)phase] * amplitude;
            updateFrequency();
        }
    }
    phaseAtBufferStart = phase;
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    const int labelSpace = 100;
    freq_slider.setBounds(labelSpace, 20, getWidth()-100, 20);
    amp_slider.setBounds(labelSpace, 50, getWidth()-100, 50);  
    
}
