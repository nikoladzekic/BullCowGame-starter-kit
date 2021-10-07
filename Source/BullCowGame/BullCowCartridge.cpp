// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words); 

    InitGame();

    PrintLine(TEXT("Number of possible words is: %i"), GetValidWords(Words).Num());
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if(bGameOver){
        ClearScreen();
        InitGame();
    } else {
        ProcessGuess(Input);
    }

}

void UBullCowCartridge::InitGame()
{
    bGameOver = false;
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)]; 
    Lives = HiddenWord.Len(); 

    PrintLine(TEXT("Welcome player!"));
    PrintLine(TEXT("Please input line and press Enter!"));

}

/* 
    Display EndGame screen
 */

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine("Press Enter to play again.");
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    
    if(HiddenWord == Guess){

        PrintLine(TEXT("Congratulations! You Won!"));
        EndGame();
        return;
    } 

    if(Lives > 1){

        if(HiddenWord.Len() != Guess.Len()){

            PrintLine(TEXT("The Hidden Word is: %i characters long.\nYou have lost!"), HiddenWord.Len());
            EndGame();
            return;
        } 

        if(!IsIsogram(Guess)){

            PrintLine(TEXT("Repeating characters are not allowed. Try again!"));
            return;
        }
        FBullCowCount Score = GetBullsCows(Guess);

        PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
        PrintLine(TEXT("Wrong guess. You have %i lives left"), --Lives);

        
    } else {

        PrintLine(TEXT("You have no lives left!"));
        EndGame();
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const{

    for(int32 Index = 0; Index != Word.Len(); ++Index){
        for(int32 Comparison = Index + 1; Comparison!= Word.Len(); ++ Comparison){

            if(Word[Index] == Word[Comparison]){
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Words) const
{
    TArray<FString> ValidWords;

    for (FString Word: Words)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullsCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            ++Count.Bulls;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                ++Count.Cows;
                break;
            }
        }
        
    }

    return Count;
    
}