// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputSystemComponent.generated.h"

class UInputConfig;
class UInputAction;
class UInputResponse;

class APlayerController;
class UEnhancedInputLocalPlayerSubsystem;

USTRUCT()
struct FRuntimeInputBinding
{
	GENERATED_BODY()

	int32 TriggeredHandle = INDEX_NONE;
	int32 StartedHandle = INDEX_NONE;
	int32 CompletedHandle = INDEX_NONE;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INPUTSYSTEM_API UInputSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	TWeakObjectPtr<APlayerController> m_PlayerController = nullptr;
	TWeakObjectPtr<UEnhancedInputLocalPlayerSubsystem> m_EnhancedInputLocalPlayerSubsystem = nullptr;
public:	
	UInputSystemComponent();

	APlayerController* RefreshPlayerController();
	UEnhancedInputLocalPlayerSubsystem* RefreshEnhancedInputLocalPlayerSubsystem();

	APlayerController* GetPlayerController();
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem();

	UFUNCTION(BlueprintCallable)
	void AddedInputConfig(UInputConfig* InputConfig);

	UFUNCTION(BlueprintCallable)
	void RemoveInputConfig(UInputConfig* InputConfig);

protected:
	UPROPERTY()
	TMap<UInputAction*, UInputResponse*> RuntimeActions;

	UPROPERTY()
	TMap<UInputAction*, FRuntimeInputBinding> RuntimeInputBindings;
};
