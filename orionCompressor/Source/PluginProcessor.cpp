/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OrionCompressorAudioProcessor::OrionCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     
                      
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       //.withInput  ("Sidechain", AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                       )
#endif
{
    
    
    
}

OrionCompressorAudioProcessor::~OrionCompressorAudioProcessor()
{
    
    
}

//==============================================================================
const String OrionCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OrionCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OrionCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OrionCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OrionCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OrionCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OrionCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OrionCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const String OrionCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void OrionCompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OrionCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    bufferSize = samplesPerBlock;
    sample_rate = sampleRate;
    M = round(getTotalNumInputChannels()/2.0);
    
    
    //allocate dynamic memory
    x_g.allocate(bufferSize, true);
    x_l.allocate(bufferSize, true);
    y_g.allocate(bufferSize, true);
    y_l.allocate(bufferSize, true);
    c.allocate(bufferSize, true);
    yL_prev = 0.0;
    
    //autoTime = false;
    compressorONOFF = false;
    resetAll();
    
    
}

void OrionCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OrionCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
    
    //layouts.getMainInputChannelSet().isDisabled();
    return true;
  #endif
}
#endif

void OrionCompressorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (compressorONOFF)
    {
        inputBuffer.setSize(M,bufferSize);
        inputBuffer.clear();
        for (int m = 0 ; m < M ; ++m)
        {
            if ( (threshold< 0) )
            {
                inputBuffer.clear(m,0,bufferSize);
                // Mix down left-right to analyse the input
                inputBuffer.addFrom(m,0,buffer,m*2,0,bufferSize,0.5);
                inputBuffer.addFrom(m,0,buffer,m*2+1,0,bufferSize,0.5);
                // compression : calculates the control voltage
                compressor(inputBuffer,m);
                // apply control voltage to the audio signal
                for (int i = 0 ; i < bufferSize ; ++i)
                {
                    buffer.getWritePointer(2*m+0)[i] *= c[i];
                    buffer.getWritePointer(2*m+1)[i] *= c[i];
                }
                inputBuffer.clear(m,0,bufferSize);
                // Mix down left-right to analyse the output
                inputBuffer.addFrom(m,0,buffer,m*2,0,bufferSize,0.5);
                inputBuffer.addFrom(m,0,buffer,m*2+1,0,bufferSize,0.5);
            }
        }
    }

}


// compressor functions
void OrionCompressorAudioProcessor::compressor(AudioSampleBuffer &buffer, int m)
{
    alphaAttack = exp(-1/(0.001 * sample_rate * tauAttack));
    alphaRelease= exp(-1/(0.001 * sample_rate * tauRelease));
    for (int i = 0 ; i < bufferSize ; ++i)
    {
        //Level detection- estimate level using peak detector
        if (fabs(buffer.getWritePointer(m)[i]) < 0.000001) x_g[i] =-120;
        else x_g[i] =20*log10(fabs(buffer.getWritePointer(m)[i]));
        //Gain computer- static apply input/output curve
        if (x_g[i] >= threshold) y_g[i] = threshold+ (x_g[i] - threshold) / ratio;
        else y_g[i] = x_g[i];
        x_l[i] = x_g[i] - y_g[i];
        //Ballistics- smoothing of the gain
        if (x_l[0]>yL_prev)  y_l[i]=alphaAttack * yL_prev+(1 - alphaAttack ) * x_l[i] ;
        else                 y_l[i]=alphaRelease* yL_prev+(1 - alphaRelease) * x_l[i] ;
        //find control
        c[i] = pow(10,(makeUpGain - y_l[i])/20);
        yL_prev=y_l[i];
    }
}


void OrionCompressorAudioProcessor::resetAll()
{
    tauAttack=0;tauRelease = 0;
    alphaAttack=0;alphaRelease = 0;
    threshold = 0;
    ratio= 1;
    makeUpGain= 0;
    yL_prev=0;
    for (int i = 0 ; i < bufferSize ; ++i)
    {
        x_g[i] = 0;    y_g[i] = 0;
        x_l[i] = 0;    y_l[i] = 0;
        c[i] = 0;
    }
}


//==============================================================================
int OrionCompressorAudioProcessor::round(float inn)
{
    if (inn > 0) return (int) (inn + 0.5);
    else return (int) (inn - 0.5);
}

template <class T> const T& OrionCompressorAudioProcessor::max( const T& a, const T& b )
{
    return (a < b) ? b : a;
}

//////////////////////////////////////////////
float OrionCompressorAudioProcessor::getThreshold()
{
    return threshold;
}
float OrionCompressorAudioProcessor::getRatio()
{
    return ratio;
}
float OrionCompressorAudioProcessor::getGain()
{
    return makeUpGain;//problem?
}
float OrionCompressorAudioProcessor::getAttackTime()
{
    return tauAttack;
}
float OrionCompressorAudioProcessor::getReleaseTime()
{
    return tauRelease;
}
////////////////////////////////////////////////////////
void OrionCompressorAudioProcessor::setThreshold(float T)
{
    threshold= T;
}
void OrionCompressorAudioProcessor::setGain(float G)
{
    makeUpGain= G;
}
void OrionCompressorAudioProcessor::setRatio(float R)
{
    ratio= R;
}
void OrionCompressorAudioProcessor::setAttackTime(float A)
{
    tauAttack = A;
}
void OrionCompressorAudioProcessor::setReleaseTime(float R)
{
    tauRelease = R;
}










//==============================================================================
bool OrionCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OrionCompressorAudioProcessor::createEditor()
{
    return new OrionCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void OrionCompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OrionCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OrionCompressorAudioProcessor();
}
