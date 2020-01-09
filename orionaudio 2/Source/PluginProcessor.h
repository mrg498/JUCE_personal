/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "./SimpleSynth.h"

//==============================================================================
/**
*/
class OrionaudioAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    OrionaudioAudioProcessor();
    ~OrionaudioAudioProcessor();

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
    void fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void getFromDelayBuffer(AudioBuffer<float>& buffer,int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    AudioTransportSource transport;
    //std::unique_ptr<AudioFormatReaderSource> playSource;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionaudioAudioProcessor)
    SimpleSynth synth;
    AudioProcessorValueTreeState tree;
    AudioBuffer<float> mDelayBuffer;
    AudioBuffer<float> tempbuffer;
    int mWritePosition { 0 };
    int mSampleRate { 44100 }; //typo
};
