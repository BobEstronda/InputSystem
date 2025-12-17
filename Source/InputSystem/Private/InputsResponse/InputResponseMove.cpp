// Fill out your copyright notice in the Description page of Project Settings.


#include "InputsResponse/InputResponseMove.h"

#include "GameFramework/Character.h"

void UInputResponseMove::Triggered(const FInputActionValue& Value)
{
    if (!OwningActor) return;

    ACharacter* Character = Cast<ACharacter>(OwningActor);
    if (!Character) return;

    FVector2D MoveVector = Value.Get<FVector2D>();

    Character->AddMovementInput(Character->GetActorForwardVector(), MoveVector.Y);
    Character->AddMovementInput(Character->GetActorRightVector(), MoveVector.X);
}
