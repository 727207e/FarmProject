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
    FTransform Transform;

    UPROPERTY()
    FDateTime Date;
};
