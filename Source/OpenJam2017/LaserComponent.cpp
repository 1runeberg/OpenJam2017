// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#include "LaserComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
ULaserComponent::ULaserComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void ULaserComponent::BeginPlay()
{
	Super::BeginPlay();

	// Iterate through all laser beams and set custom properties
	for (int32 i = 0; i < LaserBeams.Num(); i++)
	{
		if (LaserBeams[i].LaserMesh->IsValidLowLevel())
		{
			// Create StaticMesh Component
			LaserBeams[i].LaserMeshComponent = NewObject<UStaticMeshComponent>(this);
			LaserBeams[i].LaserMeshComponent->RegisterComponentWithWorld(GetWorld());
			LaserBeams[i].LaserMeshComponent->SetMobility(EComponentMobility::Movable);
			LaserBeams[i].LaserMeshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
			LaserBeams[i].LaserMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			LaserBeams[i].LaserMeshComponent->SetStaticMesh(LaserBeams[i].LaserMesh);

			// Set the laser material if available
			if (LaserBeams[i].LaserMaterial->IsValidLowLevel())
			{
				LaserBeams[i].LaserMeshComponent->SetMaterial(0, LaserBeams[i].LaserMaterial);
			}
			
			// Set transform offsets
			LaserBeams[i].LaserMeshComponent->AddLocalTransform(LaserBeams[i].TransformOffset);
		}
	}
	
}


// Called every frame
void ULaserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Scale lasers
	if (bIsScaling)
	{
		for (int32 i = 0; i < LaserBeams.Num(); i++)
		{
			if (LaserBeams[i].LaserMeshComponent->IsValidLowLevel())
			{
				// Scale mesh
				LaserBeams[i].LaserMeshComponent->SetWorldScale3D(FVector(LaserBeams[i].LaserMeshComponent->GetComponentScale().X + LaserScaleFactor.X,
					LaserBeams[i].LaserMeshComponent->GetComponentScale().Y + LaserScaleFactor.Y,
					LaserBeams[i].LaserMeshComponent->GetComponentScale().Z + LaserScaleFactor.Z)
				);
			}

		}

		// Check if we've reached the max distance, based on range
		if (LaserBeams.Num() > 0 
			&& LaserBeams[LaserBeams.Num()-1].LaserMeshComponent->IsValidLowLevel()
			&& LaserBeams[LaserBeams.Num()-1].LaserMeshComponent->GetComponentScale().X > Range
			)
		{
			//bIsScaling = false;
		}
	}
}


// Fire all lasers
void ULaserComponent::FireLasers()
{
	// Face lasers to target location
	for (int32 i = 0; i < LaserBeams.Num(); i++)
	{
		if (LaserBeams[i].LaserMeshComponent->IsValidLowLevel())
		{
			// Calculate the target location
			FVector TargetLocation = this->GetComponentLocation() + (this->GetComponentRotation().Vector() * Range);

			// Find the laser rotation 
			FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(LaserBeams[i].LaserMeshComponent->GetComponentLocation(), TargetLocation);

			// Set the rotation of the laser to face the target location
			LaserBeams[i].LaserMeshComponent->SetWorldRotation(TargetRotation);


		}

	}

	// Allow scaling of lasers
	bIsScaling = true;
}
