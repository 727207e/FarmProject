// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPBuildingInfoComponent.generated.h"


UCLASS(Blueprintable)
class FARMPROJECT_API UFPBuildingInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFPBuildingInfoComponent();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
};
