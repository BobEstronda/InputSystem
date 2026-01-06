// Fill out your copyright notice in the Description page of Project Settings.


#include "InputResponse.h"

void UInputResponse::Triggered(const FInputActionValue& Value)
{
	OnTriggered(Value);
}

void UInputResponse::Started(const FInputActionValue& Value)
{
	OnStarted(Value);
}

void UInputResponse::Completed(const FInputActionValue& Value)
{
	OnCompleted(Value);
}

void UInputResponse::OnTriggered_Implementation(const FInputActionValue& Value)
{
}

void UInputResponse::OnStarted_Implementation(const FInputActionValue& Value)
{
}

void UInputResponse::OnCompleted_Implementation(const FInputActionValue& Value)
{
}
