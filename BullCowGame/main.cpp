/* This is the console executable, that makes use of the BullCowGame class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// basic types substitution to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// helper functions prototypes as outside a class
//void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game which  we re-use across play

// the entry point for our application
int main() 
{
	do {
		//PrintIntro();
		PlayGame();
	} 
	while ( AskToPlayAgain() == true);
	
	return 0;
}



// plays a single game to completion
void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remain
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << " ";
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives the valid guess
FText GetValidGuess() 
{	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check if the guess is valid
		Status = BCGame.CheckGuessValidaty(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please, enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please, enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get valid input
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play with the same hidden word again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "CONGRATULATIONS - YOU WON!\n";
	}
	else
	{
		std::cout << "You LOST. Better luck next time.\n";
	}
}

/* GAME MECHANICS WISHLIST:
	1) Implement more words (some txt file, with available isograms picked randomly)
	with possibility of picking n-letter word to play.
	2) Easy mode with some hints.
	3) Display enigmatic word after lose, if don't want to play again.
	4) Richer design)
*/
