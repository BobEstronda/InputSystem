// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputResponse.h"
#include "InputResponseLook.generated.h"

UCLASS()
class INPUTSYSTEM_API UInputResponseLook : public UInputResponse
{
	GENERATED_BODY()
	
public:
	virtual void Triggered(const FInputActionValue& Value) override;
};
