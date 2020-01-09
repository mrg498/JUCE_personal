/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginAudioProcessor::DelayPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DelayPluginAudioProcessor::~DelayPluginAudioProcessor()
{
}

//==============================================================================
const String DelayPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String DelayPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}




//==============================================================================
void DelayPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mySampleRate = sampleRate;
    
    
    
    const int delayBufferSize = 2 * sampleRate; //calculate delayBuffer size to be 2 seconds worth of samples
    
    int numChannels = getTotalNumInputChannels(); // get total number of channels
    
    delayBuffer.setSize(numChannels, delayBufferSize); //allocate buffer size (like malloc)
    delayBuffer.clear();

    
}

void DelayPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// ideas for future work-- fft delay, 
// fft delay? delay frequencies differently
void DelayPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //clear buffer
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    
    
    
    // fill delay buffer
    for(int channel = 0; channel < totalNumInputChannels; channel++)
    {
        
        bufferData = buffer.getReadPointer(channel);
        delayBufferData = delayBuffer.getReadPointer(channel);
        delayBottom = buffer.getReadPointer(channel, 0);
        delayTop = delayBuffer.getReadPointer(channel, delayBuffer.getNumSamples());
        
        
        // first we need to fill the delay buffer with the incoming block. The delay buffer basically
        // works like a queue, so we want to implement it as a FIFO structure
        // to do this we need to keep track of a writePosition to see where we can enqueue the newest block
        
        //delayBufGain scales the amplitude of the signals being added to the delay buffer
        
        //delayBufGain = 0.5;////////////////
        
        //feedBackGain scales the amplitude of the signal being added back into the delay buffer
        //feedBackGain = 0.5; /////////////////
        
        
        
        //if there is enough space for an entire block of new samples, we just add them in
        if(delayBuffer.getNumSamples() > buffer.getNumSamples() + writePosition)
        {
            //this is how you copy samples from one buffer to another in JUCE
            delayBuffer.copyFromWithRamp(channel, writePosition, bufferData, buffer.getNumSamples(), delayBufGain, delayBufGain);
            
        }
        //if there is not enough space, we use the rest of the available space in the delay buffer, and then
        // we start overwriting the oldest samples by wrapping around to the beginning of the delay buffer
        // this creates our circular buffer
        else
        {
            // to get the remaing space available at the end of the delayBuffer, we get the difference in samples
            // between our total delayBuffer size and the current position we have written up to
            delayBufRemaining = delayBuffer.getNumSamples() - writePosition;
            
            delayBuffer.copyFromWithRamp(channel, writePosition, bufferData, delayBufRemaining, delayBufGain, delayBufGain);
            
            delayBuffer.copyFromWithRamp(channel, 0, bufferData + delayBufRemaining, buffer.getNumSamples() - delayBufRemaining, delayBufGain, delayBufGain);
            
        }
        
        //retrieve from delay buffer and add back to buffer
        
        
        
        
        // switch delay in milliseconds to delay in samples
        int delaySamples = static_cast<int>(mySampleRate/1000.0 * delay);
        
        
        // when getting our read position, we calculate our position by counting past the top of our buffer
        // if we didn't do it this way we would have to deal with negative modulo which is confusing
        const int readPosition = (delayBuffer.getNumSamples() + writePosition - delaySamples) % delayBuffer.getNumSamples();
        
        // if we can get a full block worth of samples between our read position and the end of the buffer
        // we just add them on top of the samples in the current block
        if(delayBuffer.getNumSamples() > readPosition + buffer.getNumSamples())
        {
            // addFromWithRamp adds the specified delay signal from the delay buffer to the current blocks
            // existing signal
            buffer.addFromWithRamp(channel, 0, delayBufferData + readPosition, buffer.getNumSamples(),outputGain,outputGain);
            
        }
        else
        {
            //similar process to above
            delayBufRemaining = delayBuffer.getNumSamples() - readPosition;
            buffer.addFromWithRamp(channel, 0, delayBufferData + readPosition, delayBufRemaining,outputGain,outputGain);
            buffer.addFromWithRamp(channel, delayBufRemaining, delayBufferData, buffer.getNumSamples() - delayBufRemaining,outputGain,outputGain);
            
        }
        
        
        //Finally, we want to add back the combination of the delayed and dry signal in the new block to
        // the delay buffer to create a feedback loop
        
        if(delayBuffer.getNumSamples() > writePosition + buffer.getNumSamples())
        {
            delayBuffer.addFromWithRamp(channel, writePosition, bufferData, buffer.getNumSamples(), feedBackGain,feedBackGain);
        }
        else
        {
            delayBufRemaining = delayBuffer.getNumSamples() - writePosition;
            
            delayBuffer.addFromWithRamp(channel, writePosition, bufferData, delayBufRemaining, feedBackGain,feedBackGain);
            delayBuffer.addFromWithRamp(channel, 0, bufferData + delayBufRemaining, buffer.getNumSamples() - delayBufRemaining, feedBackGain,feedBackGain);
        }
        
    }
    
    
    //After each block we update the write pointer position by increments of the block size
    writePosition += buffer.getNumSamples();
    
    // If we get to the end of the delay buffer, we need to wrap around to the beginning again
    writePosition %= delayBuffer.getNumSamples();
    
    
}
//==============================================================================



//==============================================================================



//==============================================================================
bool DelayPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DelayPluginAudioProcessor::createEditor()
{
    return new DelayPluginAudioProcessorEditor (*this);
}

//==============================================================================
void DelayPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DelayPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayPluginAudioProcessor();
}
