// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount 
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void EndGame();
	void ProcessGuess(const FString&);
	bool IsIsogram(const FString&) const;
	TArray<FString> GetValidWords(const TArray<FString>& Words) const;
	FBullCowCount GetBullsCows(const FString&) const;

	
	private:
	int32 Lives;
	FString HiddenWord;
	bool bGameOver;
	TArray<FString> Isograms;
	
};
