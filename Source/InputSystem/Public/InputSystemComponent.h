// Copyright 2026 Alessandro Cristoffer

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

USTRUCT()
struct FInputConfigContext
{
	GENERATED_BODY()

	//int32 TriggeredHandle = INDEX_NONE;
	//int32 StartedHandle = INDEX_NONE;
	//int32 CompletedHandle = INDEX_NONE;

	UPROPERTY()
	TMap<UInputAction*, UInputResponse*> RuntimeActions;
	UPROPERTY()
	TMap<UInputAction*, FRuntimeInputBinding> RuntimeInputBindings;

	void AddedRuntimeAction(UInputAction* InputAction, UInputResponse* InputResponse)
	{
		RuntimeActions.Add(InputAction, InputResponse);
	}
	void RemoveRuntimeAction(UInputAction* InputAction)
	{
		RuntimeActions.Remove(InputAction);
	}

	void AddedRuntimeInputBindings(UInputAction* InputAction, FRuntimeInputBinding& InputBinding)
	{
		RuntimeInputBindings.Add(InputAction, InputBinding);
	}
	void RemoveRuntimeInputBindinds(UInputAction* InputAction)
	{
		RuntimeInputBindings.Remove(InputAction);
	}

	UInputResponse* FindInputResponse(UInputAction* InputAction)
	{
		UInputResponse* Response = *RuntimeActions.Find(InputAction);
		return Response;
	}

	FRuntimeInputBinding& FindInputBinding(UInputAction* InputAction)
	{
		FRuntimeInputBinding& InputBinding = *RuntimeInputBindings.Find(InputAction);
		return InputBinding;
	}
};

//USTRUCT()
//struct FInputConfigBundle
//{
//	GENERATED_BODY()
//
//	TArray<UInputConfig*> AllInputConfig;
//};

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

	UFUNCTION(BlueprintCallable, Category = "Input System")
	void AddedInputConfig(UInputConfig* InputConfig);

	UFUNCTION(BlueprintCallable, Category = "Input System")
	void RemoveInputConfig(UInputConfig* InputConfig);

	UFUNCTION(BlueprintCallable, Category = "Input System")
	void BlockInputConfig(UInputConfig* InputConfig);

	UFUNCTION(BlueprintCallable, Category = "Input System")
	void UnblockInputConfig(UInputConfig* InputConfig);

	UFUNCTION(BlueprintCallable, Category = "Input System")
	void BlockInput(UInputConfig* Context, UInputAction* InputAction);

	UFUNCTION(BlueprintCallable, Category = "Input System")
	void UnblockInput(UInputConfig* Context, UInputAction* InputAction);

protected:
	//UPROPERTY()
	//TMap<UInputAction*, UInputResponse*> RuntimeActions;
	//
	//UPROPERTY()
	//TMap<UInputAction*, FRuntimeInputBinding> RuntimeInputBindings;

	UPROPERTY()
	TMap<UInputConfig*, FInputConfigContext> MappedInputConfig;

	//UPROPERTY()
	//TMap<UInputMappingContext*, FInputConfigBundle> MappedMappingContext;
};
