/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>
//==============================================================================
/**
*/
class OrionCompressorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    OrionCompressorAudioProcessor();
    ~OrionCompressorAudioProcessor();
    
   
    

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    
    //my methods,variables
    
    int bufferSize;
    
    void compressor(AudioSampleBuffer &buffer, int m); // compressor functions
    
    AudioPlayHead::CurrentPositionInfo lastPosInfo;
    
    int round(float inn);
    
    template <class T> const T& max ( const T& a, const T& b );

    
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
    float getThreshold();
    float getRatio();
    float getGain();
    float getAttackTime();
    float getReleaseTime();
    void setThreshold(float T);
    void setGain(float G);
    void setRatio(float R);
    void setAttackTime(float A);
    void setReleaseTime(float R);
    void resetAll();
    
    // parameters
    
    bool compressorONOFF;
    int M;
    bool autoTime;
    
    //==============================================================================

private:
    
    AudioBuffer<float> inputBuffer;
    
    
    //these are used to persist UI's size- values are stored along with filter's other parameters, and UI component will update them when it gets resized.
    int lastUIWidth, lastUIHeight;
    
    HeapBlock <float> x_g, x_l,y_g, y_l,c;// input, output, control
    // parameters
    float ratio,threshold,makeUpGain,tauAttack,tauRelease,alphaAttack,alphaRelease,yL_prev;
    //int nhost;
    double sample_rate;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionCompressorAudioProcessor)
};
