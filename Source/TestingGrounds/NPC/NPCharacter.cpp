// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCharacter.h"

#include "Weapons/GunBase.h"
#include "Weapons/WeaponProjectile.h"
#include "Components/SkeletalMeshComponent.h"

#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPCharacter::ANPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	//TP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP_Gun"));
	//TP_Gun->SetOnlyOwnerSee(false);			// only the owning player will see this mesh
	//TP_Gun->bCastDynamicShadow = false;
	//TP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//TP_Gun->SetupAttachment(RootComponent);
	

	//TP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	//TP_MuzzleLocation->SetupAttachment(TP_Gun);
	//TP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	//GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void ANPCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//bool AttachmentDone = TP_Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	/*if (!AttachmentDone)
	{
		UE_LOG(LogTemp, Error, TEXT("Attachment was not done"));
	}

	TP_Gun->SetVisibility(true);*/


	if (GunClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			
				const FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = FVector(0.f, 0.f, 0.f);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				TP_Gun = World->SpawnActor<AGunBase>(GunClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
		}
	}
	if (TP_Gun)
	{
		//Attach gun actor to Skeleton, doing it here because the skeleton is not yet created in the constructor
		TP_Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		TP_Gun->SetPawnOwner(this);
	}
		
}

void ANPCharacter::OnFire()
{
	if (TP_Gun)
	{
		bool WasShoot = TP_Gun->OnFire();
		if (WasShoot)
		{
			// try and play a firing animation if specified
			//if (FireAnimation != NULL)
			//{
			//	// Get the animation object for the arms mesh
			//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();	//????
			//	if (AnimInstance != NULL)
			//	{
			//		AnimInstance->Montage_Play(FireAnimation, 1.f);
			//	}
			//}
		}
	}
}

// Called every frame
//void ANPCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
//void ANPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

