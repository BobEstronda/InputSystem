// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputActionValue.h"
#include "InputResponse.generated.h"

class AActor;
class APlayerController;

UCLASS(ABSTRACT, BlueprintType, Blueprintable)
class INPUTSYSTEM_API UInputResponse : public UObject
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "InputSystem|Member")
    AActor* m_AvatarActor;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "InputSystem|Member")
    APlayerController* m_PlayerController;

public:
    virtual void Initialize(APlayerController* PlayerController, AActor* AvatarActor = nullptr);

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
