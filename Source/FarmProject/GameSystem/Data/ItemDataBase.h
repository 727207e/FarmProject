// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemDataBase.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UItemDataBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentCount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 MaxCount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UTexture2D* Image;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FText Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<UObject> BlueprintObject;
};
