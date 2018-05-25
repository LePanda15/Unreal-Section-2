#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax unreal friendly
#define TMap std::map 
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { reset(); } // Default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return BGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::reset()
{
	MyCurrentTry = 1;
	const FString HIDDEN_WORD = "planet"; // this must be an isogram
	MyHiddenWord = HIDDEN_WORD;
	BGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isnt an isogram, 
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess))// if the guess isnt all lowercase TODO write function
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength())//if guess length is worng
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// recives a valid guess, incruments turn, and returs count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount bullCowCount; 
	int32 WordLength = MyHiddenWord.length(); // Assuming same length as guess

	//loop through all lettesr in hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compareletters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// incrument bulls if theyre in the same place
			if ((MyHiddenWord[MHWChar] == Guess[GChar]) && (GChar == MHWChar))
			{
				bullCowCount.Bulls++; 
			}
			// incurment cows if not
			else if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				bullCowCount.Cows++;
			}
		}
	}

	if (bullCowCount.Bulls == WordLength)
	{
		BGameIsWon = true;
	}
	else
	{
		BGameIsWon = false;
	}

	return bullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isogram
	if (Word.length() <= 1) { return true; }

	// set up our map
	TMap<char, bool> LetterSeen;

	// Loop through all the letters  of the word
	for (auto Letter : Word) //for all letters in word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; } // Not Isogram
		else { LetterSeen[Letter] = true; }
	}
		
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() == 0) { return true; }

	// Going throug all letters of the word
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // checking if the letter is lower cased
		{ return false; } 
	}
	return true;
}
