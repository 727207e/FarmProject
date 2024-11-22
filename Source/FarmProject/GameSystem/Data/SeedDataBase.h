// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "SeedDataBase.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API USeedDataBase : public UItemDataBase
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NeedMTime;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NeedLTime;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UStaticMesh> MStaticMesh;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UStaticMesh> LStaticMesh;
};
