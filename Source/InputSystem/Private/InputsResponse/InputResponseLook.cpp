// Fill out your copyright notice in the Description page of Project Settings.


#include "InputsResponse/InputResponseLook.h"

#include "GameFramework/Character.h"

void UInputResponseLook::Triggered(const FInputActionValue& Value)
{
    if (!OwningActor) return;

    APlayerController* PC = Cast<APlayerController>(OwningActor->GetInstigatorController());
    if (!PC) return;

    FVector2D LookAxis = Value.Get<FVector2D>();

    PC->AddYawInput(LookAxis.X);
    PC->AddPitchInput(LookAxis.Y);
}
