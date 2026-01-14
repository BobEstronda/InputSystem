// Fill out your copyright notice in the Description page of Project Settings.


#include "InputsResponse/InputResponseMove.h"

#include "GameFramework/Character.h"

void UInputResponseMove::Triggered(const FInputActionValue& Value)
{
    if (!OwningActor) return;

    ACharacter* Character = Cast<ACharacter>(OwningActor);
    if (!Character) return;

    const FVector2D MoveVector = Value.Get<FVector2D>();

	const FRotator Rotation = Character->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
 
	Character->AddMovementInput(ForwardDirection, MoveVector.Y);
	Character->AddMovementInput(RightDirection, MoveVector.X);
}
