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


#include "InputResponse.h"

void UInputResponse::Initialize(APlayerController* PlayerController, AActor* AvatarActor)
{
	m_PlayerController = PlayerController;
	m_AvatarActor = AvatarActor;
}

void UInputResponse::Triggered(const FInputActionValue& Value)
{
	if (m_ResponseBlocked) return;

	OnTriggered(Value);
}

void UInputResponse::Started(const FInputActionValue& Value)
{
	if (m_ResponseBlocked) return;

	OnStarted(Value);
}

void UInputResponse::Completed(const FInputActionValue& Value)
{
	if (m_ResponseBlocked) return;

	OnCompleted(Value);
}

void UInputResponse::BlockResponse()
{
	m_ResponseBlocked = true;
}

void UInputResponse::UnblockResponse()
{
	m_ResponseBlocked = false;
}

/*
void UInputResponse::SwitchResponseBlockedState()
{
	m_ResponseBlocked = !m_ResponseBlocked;
}
*/

void UInputResponse::OnTriggered_Implementation(const FInputActionValue& Value)
{
}

void UInputResponse::OnStarted_Implementation(const FInputActionValue& Value)
{
}

void UInputResponse::OnCompleted_Implementation(const FInputActionValue& Value)
{
}