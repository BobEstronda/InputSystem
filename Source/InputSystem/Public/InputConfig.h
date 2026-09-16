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
