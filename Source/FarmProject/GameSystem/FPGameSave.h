// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FPGameSave.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPGameSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFPGameSave();

public:
	UPROPERTY()
	float MusicValue = 1.0f;

	UPROPERTY()
	float SFXValue = 1.0f;
};
