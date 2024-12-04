#pragma once

#include "CoreMinimal.h"
#include "FieldSaveForm.generated.h"

USTRUCT(BlueprintType)
struct FFieldSaveForm
{
    GENERATED_BODY()

public:
	UPROPERTY()
	int32 Id = 0;

    UPROPERTY()
    int32 ItemForm = 0; // 1 : Building , 2 : Animal

    UPROPERTY()
    FTransform Transform;

    UPROPERTY()
    FDateTime Date;

    bool operator==(const FFieldSaveForm& Other) const
    {
        return Id == Other.Id &&
            ItemForm == Other.ItemForm &&
            Transform.Equals(Other.Transform) &&
            Date == Other.Date;
    }
};
