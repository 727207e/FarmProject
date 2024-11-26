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

    //해당 데이터 캡슐화할것. 오직 get만 하게
public:
    virtual void Copy(const UItemDataBase& Other);

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 Id;

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