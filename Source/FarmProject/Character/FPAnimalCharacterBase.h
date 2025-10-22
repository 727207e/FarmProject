// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPAnimalCharacterBase.generated.h"

UCLASS()
class FARMPROJECT_API AFPAnimalCharacterBase : public AActor
{
	GENERATED_BODY()

public:
	AFPAnimalCharacterBase();

	virtual void Tick(float DeltaTime) override;

	void OnIconClickedDown();
	
protected:
	virtual void BeginPlay() override;

private:
	void FollowMousePosition();

private:
	bool bNeedFollowMousePosition = false;
};
