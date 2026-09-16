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


#include "InputsResponse/InputResponseMove.h"

#include "GameFramework/Character.h"

void UInputResponseMove::OnTriggered_Implementation(const FInputActionValue& Value)
{
	if (!m_AvatarActor) return;

	ACharacter* Character = Cast<ACharacter>(m_AvatarActor);
	if (!Character) return;

	const FVector2D MoveVector = Value.Get<FVector2D>();

	const FRotator Rotation = Character->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	Character->AddMovementInput(ForwardDirection, MoveVector.Y);
	Character->AddMovementInput(RightDirection, MoveVector.X);
}
