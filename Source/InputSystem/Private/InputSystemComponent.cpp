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


#include "InputSystemComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

#include "InputConfig.h"
#include "InputResponse.h"

UInputSystemComponent::UInputSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

APlayerController* UInputSystemComponent::RefreshPlayerController()
{
    m_PlayerController = GetOwner()->IsA<APlayerController>() ? Cast<APlayerController>(GetOwner()) : Cast<APlayerController>(GetOwner()->GetInstigatorController());

    return m_PlayerController.Get();
}

UEnhancedInputLocalPlayerSubsystem* UInputSystemComponent::RefreshEnhancedInputLocalPlayerSubsystem()
{
    m_EnhancedInputLocalPlayerSubsystem = GetPlayerController() ? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer()) : nullptr;

    return m_EnhancedInputLocalPlayerSubsystem.Get();
}

APlayerController* UInputSystemComponent::GetPlayerController()
{
    return m_PlayerController.Get() ? m_PlayerController.Get() : RefreshPlayerController();
}

UEnhancedInputLocalPlayerSubsystem* UInputSystemComponent::GetEnhancedInputLocalPlayerSubsystem()
{
    return m_EnhancedInputLocalPlayerSubsystem.Get() ? m_EnhancedInputLocalPlayerSubsystem.Get() : RefreshEnhancedInputLocalPlayerSubsystem();
}

void UInputSystemComponent::AddedInputConfig(UInputConfig* InputConfig)
{
    if (!InputConfig)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input Config is Invalid!"));
        return;
    }

    //FInputConfigBundle& ConfigBundle = *MappedMappingContext.Find(InputConfig->MappingContext);
    if (GetEnhancedInputLocalPlayerSubsystem() && InputConfig->MappingContext && !GetEnhancedInputLocalPlayerSubsystem()->HasMappingContext(InputConfig->MappingContext))
    {
        GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(InputConfig->MappingContext, 0);
    }

    FInputConfigContext ConfigContext;
    for (const auto& Mapping : InputConfig->ActionMappings)
    {
        if (Mapping.InputResponseClass)
        {
            UInputResponse* InputResponse = NewObject<UInputResponse>(this, Mapping.InputResponseClass);
            InputResponse->Initialize(GetPlayerController(), GetPlayerController()->GetPawn());

            //RuntimeActions.Add(Mapping.InputAction, InputResponse);
            ConfigContext.AddedRuntimeAction(Mapping.InputAction, InputResponse);

            if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(GetPlayerController()->InputComponent))
            {
                FRuntimeInputBinding InputBinding;
                InputBinding.TriggeredHandle = EIC->BindAction(Mapping.InputAction, ETriggerEvent::Triggered, InputResponse, &UInputResponse::Triggered).GetHandle();
                InputBinding.StartedHandle = EIC->BindAction(Mapping.InputAction, ETriggerEvent::Started, InputResponse, &UInputResponse::Started).GetHandle();
                InputBinding.CompletedHandle = EIC->BindAction(Mapping.InputAction, ETriggerEvent::Completed, InputResponse, &UInputResponse::Completed).GetHandle();

                //RuntimeInputBindings.Add(Mapping.InputAction, InputBinding);
                ConfigContext.AddedRuntimeInputBindings(Mapping.InputAction, InputBinding);
            }
        }
    }

    MappedInputConfig.Add(InputConfig, ConfigContext);
}

void UInputSystemComponent::RemoveInputConfig(UInputConfig* InputConfig)
{
    if (!InputConfig)
    {
        return;
    }

    if (GetEnhancedInputLocalPlayerSubsystem() && InputConfig->MappingContext)
    {
        GetEnhancedInputLocalPlayerSubsystem()->RemoveMappingContext(InputConfig->MappingContext);
    }

    FInputConfigContext& ConfigContex = *MappedInputConfig.Find(InputConfig);
    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(GetPlayerController()->InputComponent))
    {
        for (const auto& Mapping : InputConfig->ActionMappings)
        {
            if (!Mapping.InputAction)
            {
                continue;
            }

            const FRuntimeInputBinding& Binding = /**RuntimeInputBindings.Find(Mapping.InputAction)*/ ConfigContex.FindInputBinding(Mapping.InputAction);

            EIC->RemoveBindingByHandle(Binding.TriggeredHandle);
            EIC->RemoveBindingByHandle(Binding.StartedHandle);
            EIC->RemoveBindingByHandle(Binding.CompletedHandle);

            //RuntimeInputBindings.Remove(Mapping.InputAction);
            //
            //RuntimeActions.Remove(Mapping.InputAction);

            ConfigContex.RemoveRuntimeInputBindinds(Mapping.InputAction);
            ConfigContex.RemoveRuntimeAction(Mapping.InputAction);
        }
    }

    MappedInputConfig.Remove(InputConfig);
}

void UInputSystemComponent::BlockInputConfig(UInputConfig* InputConfig)
{
    for (const auto& Mapping : InputConfig->ActionMappings)
    {
        if (!Mapping.InputAction)
        {
            continue;
        }

        BlockInput(InputConfig, Mapping.InputAction);
    }
}

void UInputSystemComponent::UnblockInputConfig(UInputConfig* InputConfig)
{
    for (const auto& Mapping : InputConfig->ActionMappings)
    {
        if (!Mapping.InputAction)
        {
            continue;
        }

        UnblockInput(InputConfig, Mapping.InputAction);
    }
}

void UInputSystemComponent::BlockInput(UInputConfig* Context, UInputAction* InputAction)
{
    FInputConfigContext& ConfigContext = *MappedInputConfig.Find(Context);
    UInputResponse* Response = /**RuntimeActions.Find(InputAction)*/ ConfigContext.FindInputResponse(InputAction);
    if (Response)
    {
        Response->BlockResponse();
    }
}

void UInputSystemComponent::UnblockInput(UInputConfig* Context, UInputAction* InputAction)
{
    FInputConfigContext& ConfigContext = *MappedInputConfig.Find(Context);
    UInputResponse* Response = /**RuntimeActions.Find(InputAction)*/ ConfigContext.FindInputResponse(InputAction);
    if (Response)
    {
        Response->UnblockResponse();
    }
}
