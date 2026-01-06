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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSystem|Member")
    UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSystem|Member")
    TSubclassOf<UInputResponse> InputResponseClass;
};

UCLASS(BlueprintType)
class INPUTSYSTEM_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSystem|Member")
    UInputMappingContext* MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputSystem|Member")
    TArray<FInputActionMapping> ActionMappings;
};
