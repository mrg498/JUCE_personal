/*
  ==============================================================================

    SimpleSynth.cpp
    Created: 29 May 2019 9:07:54am
    Author:  Lily H

  ==============================================================================
*/

#include "SimpleSynth.h"
#define MAX_VOICES 7


void SimpleSynth::setup() {
    // add voices to our sampler
    isChokeGroupActive = false;
    for (int i = 0; i < MAX_VOICES; i++) {
        auto* voice = new OrionSamplerVoice();
        switch(i)
        {
            case KICK:
                voice->setMidiNote(36);
                break;
            case SNARE:
                voice->setMidiNote(38);
                break;
            case CLAP:
                voice->setMidiNote(39);
                break;
            case PERC:
                voice->setMidiNote(41);
                break;
            case HIHAT:
                voice->setMidiNote(42);
                break;
            case CYMBAL:
                voice->setMidiNote(43);
                break;
            case SNAP:
                voice->setMidiNote(46);
                break;
            default:
                break;
        }
        addVoice(voice);
        
    }
    audioFormatManager.registerBasicFormats();
    loadSamples();
    
}

void SimpleSynth::loadSamples()
{
   
    
    if(getNumSounds() != 0)
    {
        for(int i = 0; i < getNumSounds(); i++)
        {
            removeSound(i);
        }
    }
    int MidiNote;
    File* file;
    String filename;
    for(int i = 0; i < MAX_VOICES; i++)
    {
        switch(i)
        {
            case KICK:
                MidiNote = 36;
                filename = "/Users/milesgrossenbacher/Downloads/Drum_Kit_Sample_Data/Kicks/Kick.wav";
                break;
            case SNARE:
                MidiNote = 38;
                filename = "/Users/milesgrossenbacher/Downloads/Drum_Kit_Sample_Data/Snares/Snare.wav";
                break;
            case CLAP:
                MidiNote = 39;
                filename = "/Users/milesgrossenbacher/Downloads/Drum_Kit_Sample_Data/Claps/Clap.wav";
                break;
            case PERC:
                 MidiNote = 41;
                 filename = "/Users/milesgrossenbacher/Downloads/Drum_Kit_Sample_Data/Percs/basic-perc.wav";
                break;
            case HIHAT:
                 MidiNote = 42;
                filename = "/Users/milesgrossenbacher/Downloads/Drum_Kit_Sample_Data/Open_HH/HiHat.wav";
                break;
            case CYMBAL:
                 MidiNote = 43;
                filename = "/Users/milesgrossenbacher/Downloads/Drum_Kit_Sample_Data/Crash/Crash_01.wav";
                break;
            case SNAP:
                 MidiNote = 46;
                filename = "/Users/milesgrossenbacher/Downloads/Drum_Kit_Sample_Data/Percs/basic-perc.wav";
                break;
            default:
                break;
                
        }
        file = new File(filename);
        reader = audioFormatManager.createReaderFor(*file);
        BigInteger note;
        note.setBit(MidiNote);
        OrionSamplerSound *sampler = new OrionSamplerSound(String(i), *reader, note, MidiNote, 0.0f, 10.0f, 10.0f);
        addSound(sampler);
        
    }
    
    
    
}

void SimpleSynth::noteOn(int midiChannel,
                         int midiNoteNumber,
                         float velocity)
{
    //const ScopedLock sl(lock);
    //std::cout<<"number of sounds"<<getNumSounds();
    for(int j = 0; j < getNumSounds(); j++)
    {
        auto sound = getSound(j);
        if(sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
        {
            for(int i = 0; i < getNumVoices(); i++)
            {
                if(auto* voice = dynamic_cast<OrionSamplerVoice*>(getVoice(i)))
                {
                    //std::cout<<"can play sound "<<voice->canPlayOrionSound(midiNoteNumber);
                    //std::cout<<"current sound " << voice->getCurrentlyPlayingSound();
                    if(voice->canPlayOrionSound(midiNoteNumber) && voice->getCurrentlyPlayingSound())
                    {
                        std::cout<<"stopped voice"<<midiNoteNumber<<voice->canPlayOrionSound(midiNoteNumber);
                        stopVoice(voice, 0.0f, false);
                    }
                }
            }
            
            for(int i = 0; i < getNumVoices(); i++)
            {
                if(auto* voice = dynamic_cast<OrionSamplerVoice*> (getVoice(i)))
                {
                    if(voice->canPlayOrionSound(midiNoteNumber) && !voice->getCurrentlyPlayingSound())
                    {
                        //Logger::outputDebugString("Start Voice: " + std::to_string(i) + " with Sound: " + std::to_string(j));
                        
                        if(isChokeGroupActive && (midiNoteNumber == 42 || midiNoteNumber == 46))
                        {
                            switch(midiNoteNumber)
                            {
                                case 42:
                                    for(int i = 0; i < getNumVoices(); i++)
                                    {
                                        if(auto* voice = dynamic_cast<OrionSamplerVoice*>(getVoice(i)))
                                        {
                                            if(voice->canPlayOrionSound(46))
                                            {
                                                stopVoice(voice, 0.0f, false);
                                                break;
                                            }
                                        }
                                    }
                                case 46:
                                    for (int i = 0; i < getNumVoices(); i++)
                                    {
                                        if (auto* voice = dynamic_cast<OrionSamplerVoice*>(getVoice(i)))
                                        {
                                            if (voice->canPlayOrionSound(42))
                                            {
                                                stopVoice(voice, 0.0f, false);
                                                break;
                                            }
                                        }
                                    }
                                default:
                                    break;
                            }
                        }
                        std::cout<<"started voice "<<midiNoteNumber;
                        startVoice(voice, sound.get(), midiChannel, midiNoteNumber, velocity);
                    }
                }
            }
        }
    }
}



