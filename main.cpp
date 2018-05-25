/*
	This is the console exe, that makes use of the bullCow class 
	This acts as the view in a MVC pattern and is responsible for all user interaction.
	For game logic see the fBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

FBullCowGame BCGame; // Instantiate a new game, which we reuse across plays

// function prototypes as outside class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskRoPalyAgain();
void PrintGameSummery();


int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} 
	while (AskRoPalyAgain());
	return 0;
}

// Plays a single game to complition
void PlayGame()
{
	BCGame.reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop asking for guesses while the game isnot won
	// and there are still tries remaining
	while ((!BCGame.IsGameWon()) && (BCGame.GetCurrentTry() <= MaxTries))
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to game, and recive counts
		FBullCowCount bullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << bullCowCount.Bulls << ". Cows = " << bullCowCount.Cows << std::endl;
	}
	PrintGameSummery();
}

// Intreduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;	
	std::cout << "Can you Guess the " << BCGame.GetHiddenWordLength() << " letter isogram i'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// Loop Continually until the user givesgives a valid guess
FText GetValidGuess()
{ 
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do
	{
		// get guess from player
		std::cout << "\nTry " << BCGame.GetCurrentTry() << "of " << BCGame.GetMaxTries() << ". Enter Your Guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << Guess << " isnt an isogram.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters\n\n";
			break;
		default: // assume the guess is ok
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskRoPalyAgain()
{
	std::cout << "Do You Want To Play Again? (y/n)"<< std::endl;
	FText Response = "";
	getline(std::cin, Response);
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

void PrintGameSummery()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nWell Done - You Win!\n\n";
	}
	std::cout << "\nYou Lost, Better Luck Next Time.\n\n";
}
