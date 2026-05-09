// Fill out your copyright notice in the Description page of Project Settings.


#include "InputsResponse/InputResponseLook.h"

#include "GameFramework/Character.h"

void UInputResponseLook::Triggered(const FInputActionValue& Value)
{ 
    FVector2D LookAxis = Value.Get<FVector2D>();

    m_PlayerController->AddYawInput(LookAxis.X);
    m_PlayerController->AddPitchInput(LookAxis.Y);
}
