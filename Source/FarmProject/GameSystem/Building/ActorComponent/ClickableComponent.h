// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickableComponent.generated.h"


UCLASS(Blueprintable)
class FARMPROJECT_API UClickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UClickableComponent();

	void OnClick();
	void OnDestroySelf();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TSet<TObjectPtr<class AGridCell>> OverlappedGridSet;

};
