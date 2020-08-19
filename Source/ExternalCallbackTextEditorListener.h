/*
  ==============================================================================

    ExternalCallbackTextEditorListener.h
    Created: 19 Aug 2020 11:58:37am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ExternalCallbackTextEditorListener : public TextEditor::Listener
{

public:
	ExternalCallbackTextEditorListener(
		const std::function<void(String text)> _textChangedCallback
	) : textChangedCallback(_textChangedCallback)
	{

	}

    /** Called when the user changes the text in some way. */
    void textEditorTextChanged(TextEditor& textEditor) override
	{
		textChangedCallback(textEditor.getText());
	}

    /** Called when the user presses the return key. */
    void textEditorReturnKeyPressed(TextEditor&) override
	{
		
	}

    /** Called when the user presses the escape key. */
    void textEditorEscapeKeyPressed(TextEditor&) override
	{
		
	}

    /** Called when the text editor loses focus. */
    void textEditorFocusLost(TextEditor&) override
	{
		
	}
	
private:
	std::function<void(String text)> textChangedCallback;
};
