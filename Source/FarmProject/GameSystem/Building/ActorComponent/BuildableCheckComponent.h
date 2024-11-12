// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildableCheckComponent.generated.h"


UCLASS(Blueprintable)
class FARMPROJECT_API UBuildableCheckComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildableCheckComponent();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPlacementValid = false;

protected:
	virtual void BeginPlay() override;	

	UFUNCTION()
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMaterial> BuilableMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMaterial> NotBuilableMat;

private:
	void UpdateState();
};
