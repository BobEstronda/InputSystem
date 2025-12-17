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

void UInputSystemComponent::BeginPlay()
{
	Super::BeginPlay();

    if (!InputConfig)
    {
        UE_LOG(LogTemp, Warning, TEXT("InputConfig not set!"));
        return;
    }

    APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController());
    if (!PC) return;

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
    if (Subsystem && InputConfig->MappingContext)
    {
        Subsystem->AddMappingContext(InputConfig->MappingContext, 0);
    }

    for (const auto& Mapping : InputConfig->ActionMappings)
    {
        if (Mapping.InputResponseClass)
        {
            UInputResponse* nputResponse = NewObject<UInputResponse>(this, Mapping.InputResponseClass);
            nputResponse->Initialize(GetOwner());

            RuntimeActions.Add(Mapping.InputAction, nputResponse);

            if (UInputComponent* EIC = Cast<APlayerController>(PC)->InputComponent)
            {
                if (UEnhancedInputComponent* EIC2 = Cast<UEnhancedInputComponent>(EIC))
                {
                    EIC2->BindAction(Mapping.InputAction, ETriggerEvent::Triggered,
                        nputResponse, &UInputResponse::Triggered);
                    EIC2->BindAction(Mapping.InputAction, ETriggerEvent::Started,
                        nputResponse, &UInputResponse::Started);
                    EIC2->BindAction(Mapping.InputAction, ETriggerEvent::Completed,
                        nputResponse, &UInputResponse::Completed);
                }
            }
        }
    }
	
}

