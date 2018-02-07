/* Header file for main class, called FBullCowGame, wich implements all
game logic (no view code or direct user interaction).
The game is a simple guess the word game based on Mastermind.
*/
#pragma once

#include <string>

// basic types substitution to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// statuses for guess validating
enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;	
	EGuessStatus CheckGuessValidaty(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	// see constructor for initialization 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	const FString HIDDEN_WORDS[20] = {
		"job", "mud", "cow", "rat", "big", "milk", "hand", "king",
		"crew", "gold", "thief", "crown", "plane", "pegas", "money", "castle", "jungle",
		"famous", "spider", "master"
	}; // those MUST be an isogram
};