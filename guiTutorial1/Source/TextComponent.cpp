/*
  ==============================================================================

    TextComponent.cpp
    Created: 14 Jul 2018 7:50:16pm
    Author:  Miles Grossenbacher

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TextComponent.h"

//==============================================================================
TextComponent::TextComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TextComponent::~TextComponent()
{
}

void TextComponent::paint (Graphics& g)
{
    Font fontType("HanziPen TC", "Regular", 30.0f);
    g.setFont(fontType);
    g.drawText("I drew a house", 0, 10, 600, 10, Justification::centredTop);
}

void TextComponent::resized()
{
  

}
