#pragma once
#include <string>
#include <string>
#include <iostream>

template <int32_t stringLength>
struct SDBMHashCalculator
{
	static inline int32_t calculate(const char8_t* const stringToHash, int32_t& value)
	{
		int32_t character = SDBMCalculator<stringLength - 1>::Calculate(stringToHash, value);
		value = character + (value << 6) + (value << 16) - value;
		return stringToHash[stringLength - 1];
	}

	static inline int32_t calculateValue(const char8_t* const stringToHash)
	{
		int32_t value = 0;
		int32_t character = SDBMCalculator<stringLength>::Calculate(stringToHash, value);
		value = character + (value << 6) + (value << 16) - value;
		return value;
	}
};

template <>
struct SDBMHashCalculator<1>
{
	static inline int32_t calculate(const char* const stringToHash, int32_t& value)
	{
		return stringToHash[0];
	}
};


inline int32_t SDBMHash(const std::string& key)
{
	int32_t result = 0;

	for (uint32_t i = 0; i < key.length(); ++i)
	{
		uint32_t c = key[i];
		result = c + (result << 6) + (result << 16) - result;
	}

	return result;
}