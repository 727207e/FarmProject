#pragma once

#include "CoreMinimal.h"
#include "ItemSaveForm.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8 {
    Plant,
    Building,
    Consumable
};

USTRUCT(BlueprintType)
struct FItemSaveForm
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 CurrentCount;

    UPROPERTY()
    int32 MaxCount;

    UPROPERTY()
    UTexture2D* Image;

    UPROPERTY()
    FText Name;

    UPROPERTY()
    TSubclassOf<UObject> BlueprintObject;
};
