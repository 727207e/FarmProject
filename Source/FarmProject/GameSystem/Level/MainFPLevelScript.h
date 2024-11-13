// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/Level/FPLevelScript.h"
#include "GameSystem/Level/Interface/BuildManagerInterface.h"
#include "MainFPLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API AMainFPLevelScript : public AFPLevelScript, public IBuildManagerInterface 
{
	GENERATED_BODY()
	
public:
	AMainFPLevelScript();

	virtual void ActiveBuildMode() override;
	virtual void DeactiveBuildMode() override;
	virtual void SpawnBuilding() override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGridManager> GridManagerREF;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UGridManager> GridManager;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> PlaceableActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlaceableActorREF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UBuildableCheckComponent> BuildableCheckComponentREF;

	UPROPERTY()
	TObjectPtr<class APlayerController> PlayerCont;

	UPROPERTY()
	FTimerHandle TimerHandle;

private:
	void SetPlacementModeEnable(bool IsEnabled);
	void UpdatePlacement();

private:
	bool bIsTouch;
	bool bIsPlacementModeEnable = false;

};