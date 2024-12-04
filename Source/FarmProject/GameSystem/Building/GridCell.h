// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCell.generated.h"

UENUM(BlueprintType)
enum class EBuildState : uint8
{
	Wait UMETA(DisplayName = "Wait"),
	Buildable UMETA(DisplayName = "Buildable"),
	NotBuildable UMETA(DisplayName = "Not Buildable"),
	OverlapBuilding UMETA(DisplayName = "Overlap Building")
};

UCLASS()
class FARMPROJECT_API AGridCell : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridCell();

	void CheckBuilding();

	void ResetGridState();
	void UpdateGridState(EBuildState CurState);
	FORCEINLINE EBuildState GetBuildState() { return MyState; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> GridMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMaterial> NormalMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMaterial> BuilableMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMaterial> NotBuilableMat;

private:
	EBuildState MyState = EBuildState::Wait;
};
