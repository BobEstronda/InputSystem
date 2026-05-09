// Fill out your copyright notice in the Description page of Project Settings.


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

    if (GetEnhancedInputLocalPlayerSubsystem() && InputConfig->MappingContext)
    {
        GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(InputConfig->MappingContext, 0);
    }

    for (const auto& Mapping : InputConfig->ActionMappings)
    {
        if (Mapping.InputResponseClass)
        {
            UInputResponse* InputResponse = NewObject<UInputResponse>(this, Mapping.InputResponseClass);
            InputResponse->Initialize(GetPlayerController(), GetPlayerController()->GetPawn());

            RuntimeActions.Add(Mapping.InputAction, InputResponse);

            if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(GetPlayerController()->InputComponent))
            {
                FRuntimeInputBinding InputBinding;
                InputBinding.TriggeredHandle = EIC->BindAction(Mapping.InputAction, ETriggerEvent::Triggered, InputResponse, &UInputResponse::Triggered).GetHandle();
                InputBinding.StartedHandle = EIC->BindAction(Mapping.InputAction, ETriggerEvent::Started, InputResponse, &UInputResponse::Started).GetHandle();
                InputBinding.CompletedHandle = EIC->BindAction(Mapping.InputAction, ETriggerEvent::Completed, InputResponse, &UInputResponse::Completed).GetHandle();

                RuntimeInputBindings.Add(Mapping.InputAction, InputBinding);
            }
        }
    }
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

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(GetPlayerController()->InputComponent))
    {
        for (const auto& Mapping : InputConfig->ActionMappings)
        {
            if (!Mapping.InputAction)
            {
                continue;
            }

            const FRuntimeInputBinding& Binding = *RuntimeInputBindings.Find(Mapping.InputAction);

            EIC->RemoveBindingByHandle(Binding.TriggeredHandle);
            EIC->RemoveBindingByHandle(Binding.StartedHandle);
            EIC->RemoveBindingByHandle(Binding.CompletedHandle);

            RuntimeInputBindings.Remove(Mapping.InputAction);

            RuntimeActions.Remove(Mapping.InputAction);
        }
    }
}
