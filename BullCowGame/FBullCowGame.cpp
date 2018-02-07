// FBullCowGame implementation. For purposes watch header file.
#pragma once

#include "FBullCowGame.h"
#include <map>
#include <ctime>

#define TMap std::map // to make more Unreal friendly
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLegthToMaxTries{ {3,5}, { 4,7}, {5,10}, {6,15},};
	return WordLegthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	srand(time(NULL));
	MyHiddenWord = HIDDEN_WORDS[rand() % 20];
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidaty(FString Guess) const
{	
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong 
	{
		return  EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// recieves a VALID guess and returns BullCowCount
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) { // if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; // increment bulls
				}
				else { // if they're not
					BullCowCount.Cows++; // increment cows
				}
			}
				
		}
	}

	if (BullCowCount.Bulls == WordLength) 
	{ 
		bGameIsWon = true; 
	} 
	else 
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // set our map
	for (auto Letter : Word) // for all letter of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an isogram 
		} else {
			LetterSeen[Letter] = true; // add the letter to the map seen
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}
