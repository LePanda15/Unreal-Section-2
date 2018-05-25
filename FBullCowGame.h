/*
The game logic (no view code or direct user interaction)
The game is a simple guess the woed game based on mastermind
*/
#pragma once
#include <string>

// to make syntax unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

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

	// Constuctor
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void reset(); 
	// Counts Bulls & Cows, and increasing try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString  MyHiddenWord;
	bool BGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};

