// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputActionValue.h"
#include "InputResponse.generated.h"


UCLASS()
class INPUTSYSTEM_API UInputResponse : public UObject
{
	GENERATED_BODY()
	
public:
    UPROPERTY()
    AActor* OwningActor;

    virtual void Initialize(AActor* Owner) { OwningActor = Owner; }


    virtual void Triggered(const FInputActionValue& Value);
    virtual void Started(const FInputActionValue& Value);
    virtual void Completed(const FInputActionValue& Value);
};
