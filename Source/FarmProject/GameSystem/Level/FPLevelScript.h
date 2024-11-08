// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "FPLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API AFPLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AFPLevelScript();

	void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UFPSettingUI> UFPSettingUISubclass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UFPSettingUI> FPSettingUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundWave> BackGroundSound;
};
