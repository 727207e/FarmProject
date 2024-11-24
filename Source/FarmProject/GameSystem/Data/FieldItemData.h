// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FieldItemData.generated.h"

UENUM(BlueprintType)
enum class EFieldState : uint8
{
    None UMETA(DisplayName = "None"),
    S UMETA(DisplayName = "Small"),
    M UMETA(DisplayName = "Midium"),
    L UMETA(DisplayName = "Large")
};

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFieldItemData : public UObject
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UTexture2D* Image;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString StartTime;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NeedMTime;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NeedLTime;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<UStaticMesh> MStaticMesh;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<UStaticMesh> LStaticMesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FText ResultFarmName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 ResultCount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 PropertyID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FText Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EFieldState ECurState = EFieldState::None;
};