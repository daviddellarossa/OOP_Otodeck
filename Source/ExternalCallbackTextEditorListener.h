/*
  ==============================================================================

    ExternalCallbackTextEditorListener.h
    Created: 19 Aug 2020 11:58:37am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/// <summary>
/// Custom Listener inheriting from TextEditor::Listener.
/// It expose several methods for activation. Each of these methods can potentially execute
/// one callback function when called. At the moment, only the textEditorTextChanged is implemented.
/// All the other activation methods are pass-through.
/// The functions to be called are passed in as constructor's input parameters,
/// at the moment only one.
/// </summary>
class ExternalCallbackTextEditorListener : public TextEditor::Listener
{
public:
	ExternalCallbackTextEditorListener(
		const std::function<void(String text)> _textChangedCallback
	) : textChangedCallback(_textChangedCallback)
	{ }

    /// <summary>
    /// Called when the user changes the text in some way.
    /// </summary>
    /// <param name="textEditor">This is the TextEditor component that fired the event</param>
    void textEditorTextChanged(TextEditor& textEditor) override
	{
		textChangedCallback(textEditor.getText());
	}

    /// <summary>
    /// Called when the user presses the return key.
    /// At the moment this is not implemente as it is not used
    /// </summary>
    /// <param name="textEditor">This is the TextEditor component that fired the event</param>
    void textEditorReturnKeyPressed(TextEditor& textEditor) override
	{	}

    /// <summary>
    /// Called when the user presses the escape key.
    /// At the moment this is not implemente as it is not used
    /// </summary>
    /// <param name="textEditor">This is the TextEditor component that fired the event</param>
    void textEditorEscapeKeyPressed(TextEditor& textEditor) override
	{	}

    /// <summary>
    /// Called when the text editor loses focus.
    /// At the moment this is not implemented as it is not used
    /// </summary>
    /// <param name="textEditor">This is the TextEditor component that fired the event</param>
    void textEditorFocusLost(TextEditor& textEditor) override
	{	}
	
private:
	/// <summary>
	/// Callback function for the textEditorTextChanged event
	/// </summary>
	std::function<void(String text)> textChangedCallback;
};
