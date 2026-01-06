// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputActionValue.h"
#include "InputResponse.generated.h"


UCLASS(ABSTRACT, BlueprintType, Blueprintable)
class INPUTSYSTEM_API UInputResponse : public UObject
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "InputSystem|Member")
    AActor* OwningActor;

public:
    virtual void Initialize(AActor* Owner) { OwningActor = Owner; }

    virtual void Triggered(const FInputActionValue& Value);
    virtual void Started(const FInputActionValue& Value);
    virtual void Completed(const FInputActionValue& Value);

    // Blueprint API
public:
    UFUNCTION(BlueprintNativeEvent, Category = "InputSystem|Events")
    void OnTriggered(const FInputActionValue& Value);

    UFUNCTION(BlueprintNativeEvent, Category = "InputSystem|Events")
    void OnStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintNativeEvent, Category = "InputSystem|Events")
    void OnCompleted(const FInputActionValue& Value);
};
