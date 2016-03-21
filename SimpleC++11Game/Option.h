#pragma once
#include "PlayerOptions.h"
#include "Serializable.h"
#include "Visitable.h"
#include <memory>
#include <string>

class Player;

class Option
	: public Visitable
	, public Serializable
{
public:
	using Pointer = std::shared_ptr<Option>;

protected:
	Pointer			m_pointer{ this };
	PlayerOptions	m_chosenOption;
	std::string		m_outputText;

public:
	Option(PlayerOptions chosenOption, const std::string& outputText, const uint32_t serializableId)
		: m_chosenOption(chosenOption)
		, m_outputText(outputText)
		, Serializable(serializableId)
	{

	}

	const std::string& GetOutputText() const
	{
		return m_outputText;
	}

	virtual void evaluate(Player& player) = 0;

	virtual void onSave(std::ofstream& file) {}
	virtual void onLoad(std::ifstream& file) {}

	Pointer getPointer() const { return m_pointer; }
};