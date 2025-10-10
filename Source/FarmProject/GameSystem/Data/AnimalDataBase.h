// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "AnimalDataBase.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UAnimalDataBase : public UItemDataBase
{
	GENERATED_BODY()

public:
    virtual void Copy(const UItemDataBase& Other) override;
};
