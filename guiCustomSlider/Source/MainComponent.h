/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
    {
        float diameter = jmin(width,height);
        float radius = diameter/2;
        float centerX = x + width/2;
        float centerY = y + height/2;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + ((sliderPosProportional) * (rotaryEndAngle-rotaryStartAngle));
        
        
        Rectangle<float> dialArea(rx,ry,diameter,diameter);
        
        g.setColour(Colours::red);
        //g.drawRect(dialArea);
        g.fillEllipse(dialArea);
        
        g.setColour(Colours::black);
        //g.fillEllipse(centerX, centerY, 5, 5);
        
        Path dialTick;
        dialTick.addRectangle(0, -radius, 10.0f, radius * 0.33);
        
        g.fillPath(dialTick,AffineTransform::rotation(angle).translated(centerX,centerY));
        
        g.drawEllipse(rx, ry, diameter, diameter, 5.0f);
        
    }
    
    
};

class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    Slider dial1;
    OtherLookAndFeel otherLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
