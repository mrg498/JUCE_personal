/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OrionaudioAudioProcessorEditor::OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
,openButton("Open"),playButton("Play"),stopButton("Stop"),state(Stopped)
{
    setSize (800, 400);
    openButton.onClick = [this]/*capture this event 执行后面{}的指令*/{ openButtonClicked(); };
    addAndMakeVisible(&openButton);
    
    playButton.onClick = [this]/*capture this event 执行后面{}的指令*/{ playButtonClicked(); };
    playButton.setColour(TextButton::buttonColourId, Colours::green);
    playButton.setEnabled(true);//防止用户多次按play
    addAndMakeVisible(&playButton);
    
    stopButton.onClick = [this]/*capture this event 执行后面{}的指令*/{ stopButtonClicked(); };
    stopButton.setColour(TextButton::buttonColourId, Colours::red);
    stopButton.setEnabled(false);
    addAndMakeVisible(&stopButton);
    
    formatManager.registerBasicFormats();//
    /*9*/
    
    
}

OrionaudioAudioProcessorEditor::~OrionaudioAudioProcessorEditor()
{
}

//==============================================================================

void OrionaudioAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    
}

void OrionaudioAudioProcessorEditor::resized()
{
    openButton.setBounds(getWidth()/2 - 300, getHeight()/2 - 150, 100, 100);//draw the open button
    playButton.setBounds(getWidth()/2 - 200, getHeight()/2 - 150, 100, 100);//draw the play button
    stopButton.setBounds(getWidth()/2 - 100, getHeight()/2 - 150, 100, 100);//draw the stop button
    
}

void OrionaudioAudioProcessorEditor::openButtonClicked()
{
    FileChooser chooser("Choose a wave or AIFF File", File::getSpecialLocation(File::userDesktopDirectory/*音频文件位置*/),"*.wav; *.aiff; *.mp3"/* true, false, nullptr*/);
    
    //if the user choose a file
    if(chooser.browseForFileToOpen())
    {
        File myFile;
        //what did user choose
        myFile = chooser.getResult();
        
        //read the file
        AudioFormatReader* reader = formatManager.createReaderFor(myFile);
        //synth.loadFiles(myFile);
        //get the file ready to play
        std::unique_ptr<AudioFormatReaderSource> tempSource/*pointer*/(new AudioFormatReaderSource(reader, true));
        
        processor.transport.setSource(tempSource.get()/*pointer*/);
        
        playSource.reset(tempSource.release());
        openButton.setButtonText(reader->getFormatName());//!!!!!!!!!!测试
    }
}

void OrionaudioAudioProcessorEditor::playButtonClicked()
{
   
    transportStateChanged(Starting);
}

void OrionaudioAudioProcessorEditor::stopButtonClicked()
{
    
    transportStateChanged(Stopping);
}

void OrionaudioAudioProcessorEditor::transportStateChanged(TransportState newState)
{
    if(newState != state)
    {
        state = newState;
        
        switch(state){
            case Stopped:
                playButton.setEnabled(true);
                processor.transport.setPosition(0.0);
                break;
            case Starting:
                stopButton.setEnabled(true);
                playButton.setEnabled(false);
                processor.transport.start();
                break;
            case Stopping:
                playButton.setEnabled(true);
                stopButton.setEnabled(false);
                processor.transport.stop();
                break;
        }
    }
}



