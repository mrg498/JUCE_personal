/*
  ==============================================================================

    OrionSamplerVoice.h
    Created: 3 Jun 2019 3:57:29pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "panpos.h"
#include "OrionSamplerSound.h"

class OrionSamplerVoice : public SamplerVoice
//, public AudioProcessorValueTreeState::Listener
{
private:
    BigInteger midiNote;
    PanPos pan;
    LinearSmoothedValue<double> shaperAmp, levelAmp, panAmp;
    int index;
    int pitchVal;
    double currSampRate;
    //Variables from SamplerVoice Base Class
    double pitchRatio = 0;
    double sourceSamplePosition = 0;
    float lgain = 0, rgain = 0;
    double filterCutoff;
    double levelSlider;

    
public:
    OrionSamplerVoice() : pitchVal(0), currSampRate(48000)
    {
        pan.setPosition(0.0);
        panAmp.reset(48000, 0.01);
        panAmp.setValue(0);
    };
    
    void setMidiNote(int note)
    {
        midiNote.setBit(note);
    };

    bool canPlaySound(SynthesiserSound* sampSound) override
    {
        return ((dynamic_cast<OrionSamplerSound*>(sampSound)) != nullptr);
    };
    
    bool canPlayOrionSound(int note) const
    {
        
        return midiNote[note];
        
    };


    void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sampSound, int pitchWheel) override
    {
        
        
        if (auto* sound = dynamic_cast<OrionSamplerSound*> (sampSound))
        {
            
            pitchRatio = std::pow(2.0, ((midiNoteNumber - sound->midiRootNote) + pitchVal) / 12.0)
            * sound->sourceSampleRate / getSampleRate();
            
            sourceSamplePosition = 0.0;
            lgain = velocity;
            rgain = velocity;
        }
        else
        {
            jassertfalse; // this object can only play SamplerSounds!
        }
        
    };
    
    
    void stopNote(float velocity, bool allowTailOff) override
    {
        
        if (allowTailOff)
        {
           
        }
        else if(!allowTailOff && velocity == 0.0f)
        {
            
            clearCurrentNote();
           
        }
        
    };
    
 
    void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override
    {
        if (auto* playingSound = dynamic_cast<OrionSamplerSound*> (getCurrentlyPlayingSound().get()))
        {
            auto& data = *playingSound->getAudioData();
            const float* const inL = data.getReadPointer(0);
            const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer(1) : nullptr;
            
            float* outL = outputBuffer.getWritePointer(0, startSample);
            float* outR = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer(1, startSample) : nullptr;
            
            while (--numSamples >= 0)
            {
             
                auto pos = (int)sourceSamplePosition;
                auto alpha = (float)(sourceSamplePosition - pos);
                auto invAlpha = 1.0f - alpha;
               
                // just using a very simple linear interpolation here..
                float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
                float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
                : l;
                
           
                //Apply Pan
                //pan.setPosition(panAmp.getNextValue());
                l = pan.processLeftChannel(l);
                r = pan.processRightChannel(r);
           
                if (outR != nullptr)
                {
                    *outL++ += l;
                    *outR++ += r;
                }
                else
                {
                    *outL++ += (l + r) * 0.5f;
                }
                
                sourceSamplePosition += pitchRatio;
               
                
                if (sourceSamplePosition > playingSound->length)
                {
                   
                    clearCurrentNote();
                    break;
                }
            }
        }
    };
    
    void parameterChanged(const String &parameterID, float newValue)
    {
        if (parameterID == String("pan" + String(index)))
        {
            panAmp.setValue(newValue);
        }
    
    
    };

    void setCurrentPlaybackSampleRate(double newRate) override
    {
        SamplerVoice::setCurrentPlaybackSampleRate(newRate);
        if (currSampRate != newRate && newRate != 0)
        {
            currSampRate = newRate;
            //shaperAmp.reset(currSampRate, 0.01);
            //levelAmp.reset(currSampRate, 0.01);
            panAmp.reset(currSampRate, 0.01);
            //env.setSampleRate(currSampRate);
            //filterLeft.setSampleRate(currSampRate);
            //filterRight.setSampleRate(currSampRate);
        }
    };
    
    void setPitchVal(int pitch) { pitchVal = pitch; };
    
    int getPitchVal() { return pitchVal; };
    

    
};
