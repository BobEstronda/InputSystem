// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputSystemComponent.generated.h"

class UInputConfig;
class UInputAction;
class UInputResponse;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INPUTSYSTEM_API UInputSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputSystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputConfig* InputConfig;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TMap<UInputAction*, UInputResponse*> RuntimeActions;
};
