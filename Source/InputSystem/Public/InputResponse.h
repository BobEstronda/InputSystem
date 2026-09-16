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

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "InputSystem|Member")
    uint8 m_ResponseBlocked : 1 = 0;

public:
    virtual void Initialize(APlayerController* PlayerController, AActor* AvatarActor = nullptr);

    void Triggered(const FInputActionValue& Value);
    void Started(const FInputActionValue& Value);
    void Completed(const FInputActionValue& Value);

    //void SwitchResponseBlockedState();
    void BlockResponse();
    void UnblockResponse();

    // Blueprint and Cpp API
public:
    UFUNCTION(BlueprintNativeEvent, Category = "InputSystem|Events")
    void OnTriggered(const FInputActionValue& Value);

    UFUNCTION(BlueprintNativeEvent, Category = "InputSystem|Events")
    void OnStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintNativeEvent, Category = "InputSystem|Events")
    void OnCompleted(const FInputActionValue& Value);
};
