/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CompressorAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer,
                                        public Button::Listener,
                                        public Slider::Listener
{
public:
    //==============================================================================
    CompressorAudioProcessorEditor (CompressorAudioProcessor* ownerFilter);
    ~CompressorAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* brushedMetalDark_jpg;
    static const int brushedMetalDark_jpgSize;
    static const char* c4dm_png2;
    static const int c4dm_png2Size;
    static const char* qmul_png2;
    static const int qmul_png2Size;
    static const char* knobstrip_png;
    static const int knobstrip_pngSize;
    static const char* scaleLr_png;
    static const int scaleLr_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;



	AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    CompressorAudioProcessor* getProcessor() const
    {
        return static_cast <CompressorAudioProcessor*> (getAudioProcessor());
    }

    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> buttonONOFF;
    std::unique_ptr<Label> label;
    std::unique_ptr<Slider> sliderThreshold;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Slider> sliderRatio;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Slider> sliderGain;
    std::unique_ptr<Label> label7;
    std::unique_ptr<Slider> sliderAttack;
    std::unique_ptr<Label> label5;
    std::unique_ptr<Slider> sliderRelease;
    std::unique_ptr<Label> label6;
    Image cachedImage_brushedMetalDark_jpg_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

