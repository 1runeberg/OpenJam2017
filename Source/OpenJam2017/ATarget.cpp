// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#include "ATarget.h"
#include "Components/AudioComponent.h"

// Sets default values
AATarget::AATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AATarget::BeginPlay()
{
	Super::BeginPlay();
	
	ApplyTargetVars();
}

// Called every frame
void AATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SphereCollision->IsValidLowLevel() && OuterShellComponent->IsValidLowLevel() && AudioComponent->IsValidLowLevel())
	{
		SphereCollision->AddWorldOffset(GravityVelocity);
		OuterShellComponent->AddWorldOffset(GravityVelocity);
		AudioComponent->AddWorldOffset(GravityVelocity);
	}
}

/** Apply target variables for when called from an external class */
void AATarget::ApplyTargetVars()
{
	// Create Actor's outer shell
	if (OuterShell->IsValidLowLevel())
	{
		// Set up sphere collision component
		SphereCollision = NewObject<USphereComponent>(this);
		SphereCollision->RegisterComponentWithWorld(GetWorld());
		SphereCollision->SetMobility(EComponentMobility::Movable);
		SphereCollision->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// Set up static mesh component
		OuterShellComponent = NewObject<UStaticMeshComponent>(this);
		OuterShellComponent->RegisterComponentWithWorld(GetWorld());
		OuterShellComponent->SetMobility(EComponentMobility::Movable);
		OuterShellComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		OuterShellComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		OuterShellComponent->SetStaticMesh(OuterShell);

		// Set up sound component
		AudioComponent = NewObject<UAudioComponent>(this);
		AudioComponent->RegisterComponentWithWorld(GetWorld());
		AudioComponent->SetMobility(EComponentMobility::Movable);
		AudioComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		if (SoundFX->IsValidLowLevel())
		{
			AudioComponent->SetSound(SoundFX);
			//AudioComponent->SetVolumeMultiplier(1000.f);
		}

		// Set the material of the component
		if (OuterShellMaterial->IsValidLowLevel())
		{
			OuterShellComponent->SetMaterial(0, OuterShellMaterial);
		}

		// Apply scale
		OuterShellComponent->SetWorldScale3D(OuterShellScale);
		SphereCollision->SetWorldScale3D(OuterShellScale);

	}

	// Create Actor's inner shell
	if (InnerShell->IsValidLowLevel())
	{
		// Setup static mesh component
		InnerShellComponent = NewObject<UStaticMeshComponent>(this);
		InnerShellComponent->RegisterComponentWithWorld(GetWorld());
		InnerShellComponent->SetMobility(EComponentMobility::Movable);
		InnerShellComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		InnerShellComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InnerShellComponent->SetStaticMesh(InnerShell);

		// Set material 
		if (InnerShellMaterial->IsValidLowLevel())
		{
			InnerShellComponent->SetMaterial(0, InnerShellMaterial);
		}

		// Apply scale
		OuterShellComponent->SetWorldScale3D(OuterShellScale);

	}
}
