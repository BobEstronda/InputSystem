// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputConfig.generated.h"

class UInputAction;
class UInputResponse;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FInputActionMapping
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UInputResponse> InputResponseClass;
};

UCLASS(BlueprintType)
class INPUTSYSTEM_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UInputMappingContext* MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FInputActionMapping> ActionMappings;
};
