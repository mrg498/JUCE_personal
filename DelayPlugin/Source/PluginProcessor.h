/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class DelayPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DelayPluginAudioProcessor();
    ~DelayPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    
    //public variables
    //AudioProcessorValueTreeState parameters;
    float previousGain;
    
    
    //control parameters
    float outputGain = 1.0;
    float delayBufGain = 0.0;
    float feedBackGain = 0.0;
    float delay = 1000;
    
    
private:
    int numChannels; 
    AudioBuffer<float> delayBuffer;
    const float* bufferData;
    const float* delayBufferData;
    double mySampleRate = 44100;
    const float* delayTop; //top storage
    const float* delayBottom; //bottom storage
    float* first; //first storage in delay line
    float* last; //last storage in delay line
    int writePosition = 0;
    int delayBufRemaining;
    
    
    
    
    
    
    
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPluginAudioProcessor)
};
