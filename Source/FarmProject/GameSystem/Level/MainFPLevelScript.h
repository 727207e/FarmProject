// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/Level/FPLevelScript.h"
#include "GameSystem/Level/Interface/BuildManagerInterface.h"
#include "MainFPLevelScript.generated.h"

DECLARE_DELEGATE(FOnSpawnBuilding)

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

	void SaveCurLevel();

	void SetPlacementModeEnable(bool IsEnabled, TObjectPtr<class UBuildingItemData> TargetData = nullptr);
	FORCEINLINE void AddField(TObjectPtr<class AFPBuilding> Target) { FieldArray.Add(Target); }
	FORCEINLINE bool GetIsPlacementMode() { return bIsPlacementModeEnable; }
	FORCEINLINE bool GetIsBuildMode() { return bIsBuildModeEnable; }

	FOnSpawnBuilding OnSpawnBuilding;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGridManager> GridManagerREF;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UGridManager> GridManager;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> PlaceableActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBuildingItemData> TargetDataREF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UBuildableCheckComponent> BuildableCheckComponentREF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UClickableComponent> ClickableComponentREF;

	UPROPERTY()
	TObjectPtr<class APlayerController> PlayerCont;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	TArray<TObjectPtr<class AFPBuilding>> FieldArray;

private:
	void UpdatePlacement();

private:
	bool bIsTouch;
	bool bIsPlacementModeEnable = false;
	bool bIsBuildModeEnable = false;

};