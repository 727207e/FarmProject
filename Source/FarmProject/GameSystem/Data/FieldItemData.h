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

DECLARE_DELEGATE_OneParam(FOnNextState, EFieldState);

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFieldItemData : public UObject
{
	GENERATED_BODY()
	
public:
    FOnNextState OnNextState;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UTexture2D* Image;

    void InitStartTime();
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FDateTime StartTime;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FDateTime NextNeedTime;

    void NextState();
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NeedMTime;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NeedLTime;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UStaticMesh> MStaticMesh;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UStaticMesh> LStaticMesh;

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

    bool operator<(const UFieldItemData& Other) const
    {
        return NextNeedTime < Other.NextNeedTime;
    }
};