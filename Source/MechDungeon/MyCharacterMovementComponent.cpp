// Fill out your copyright notice in the Description page of Project Settings.

#include "MechDungeon.h"
#include "MyCharacterMovementComponent.h"


void ACharacter::CheckJumpInput(float DeltaTime)
{
	const bool bWasJumping = bPressedJump && JumpKeyHoldTime > 0.0f;
	if (bPressedJump)
	{
		const bool bDidJump = CanJump() && CharacterMovement && CharacterMovement->DoJump(bClientUpdating);

		// Increment our timer ONLY when jumping occurs, so calls to IsJumpProvidingForce() will return true only when jumping is actually occurring
		if (bDidJump)
			JumpKeyHoldTime += DeltaTime;

		if (!bWasJumping && bDidJump)
		{
			// Increment Jump Count here so that it only happens when a new jump actually occurs
			CurrentJumpCount++;

			OnJumped();
		}
	}
}

bool ACharacter::CanJumpInternal_Implementation() const
{

	const bool bCanHoldToJumpHigher = GetJumpMaxHoldTime() > 0.0f && IsJumpProvidingForce();
	const bool bHasRemainingJumps = CurrentJumpCount < MaxJumpCount;

	return !bIsCrouched && CharacterMovement && (CharacterMovement->IsMovingOnGround() || bCanHoldToJumpHigher || bHasRemainingJumps) && CharacterMovement->CanEverJump() && !CharacterMovement->bWantsToCrouch;
}

void ACharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	CurrentJumpCount = 0;
}