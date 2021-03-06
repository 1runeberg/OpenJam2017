// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#include "LaserComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"


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

	GenerateLasers();
	
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

				// Line trace
				FVector TargetLocation = LaserBeams[i].LaserMeshComponent->GetComponentLocation() +
					(LaserBeams[i].LaserMeshComponent->GetComponentRotation().Vector() * LaserBeams[i].LaserMeshComponent->GetComponentScale().X);

				FHitResult TestHit;
				FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
				bool bHit = GetWorld()->LineTraceSingleByObjectType(
					TestHit,
					LaserBeams[i].LaserMeshComponent->GetComponentLocation(),
					TargetLocation,
					FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
					TraceParameters
					);

				// DEBUG: Test what we hit
				//if (bHit && TestHit.GetActor()->IsValidLowLevel())
				//{
				//	UE_LOG(LogTemp, Warning, TEXT("Actor hit is %s"), *TestHit.GetActor()->GetName());
				//}

				// Check if we hit something and that it is a valid target
				if (bHit && TestHit.GetActor()->IsValidLowLevel() && TestHit.GetActor()->IsA<AATarget>())
				{
					AATarget* TestTarget = Cast<AATarget>(TestHit.GetActor());

					if (TestTarget)
					{
						TestTarget->AudioComponent->Play();
						//UE_LOG(LogTemp, Warning, TEXT("KABOOM! Sound is %s"), *TestTarget->AudioComponent->Sound->GetName());

						// If it is, then destroy the target
						HitTarget = TestTarget;
					}



					// Then destroy this component and all its' children
					FTimerHandle UnusedHandle;
					GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &ULaserComponent::DestroyThis, .5f, false);
				}

			}

		}

		// Check if we've reached the max distance, based on range
		if (LaserBeams.Num() > 0 
			&& LaserBeams[LaserBeams.Num()-1].LaserMeshComponent->IsValidLowLevel()
			&& LaserBeams[LaserBeams.Num()-1].LaserMeshComponent->GetComponentScale().X > Range
			)
		{
			//UE_LOG(LogTemp, Warning, TEXT("SHRINK!"));

			// Stop laser from scaling
			bIsScaling = false;

			// Make laser shrink
			bIsShrinking = true;
		}
	}
	else if (bIsShrinking)
	{
		// Move the component forward x units
		//OriginalLocation += LaserShrinkFactor;
		this->AddWorldOffset(FVector(8.f, -.08f, 0.0f));


		// Reduce laser beams' scale by x units
		for (int32 i = 0; i < LaserBeams.Num(); i++)
		{
			if (LaserBeams[i].LaserMeshComponent->IsValidLowLevel())
			{
				//LaserBeams[i].LaserMeshComponent->AddWorldOffset(FVector(.1f,0.f,0.0f));

				//UE_LOG(LogTemp, Warning, TEXT("Shrink factor is %s"), *LaserShrinkFactor.ToString());

				// Set Beam rotation
				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(LaserBeams[i].LaserMeshComponent->GetComponentLocation(), OriginalLocation);
				LaserBeams[i].LaserMeshComponent->SetWorldRotation(TargetRotation);

				// Scale mesh
				LaserBeams[i].LaserMeshComponent->SetWorldScale3D(LaserBeams[i].LaserMeshComponent->GetComponentScale()-LaserShrinkFactor);
			}

		}

		// Check if we've reached 0 scale, destroy this component
		if (LaserBeams.Num() > 0
			&& LaserBeams[LaserBeams.Num() - 1].LaserMeshComponent->IsValidLowLevel()
			&& LaserBeams[LaserBeams.Num() - 1].LaserMeshComponent->GetComponentScale().X < .5f)
		{
			// Disable all tick activities
			bIsScaling = false;
			bIsShrinking = false;

			DestroyThis();

		}
	}
}


// Fire all lasers
void ULaserComponent::FireLasers()
{
	// Calculate the target location
	FVector TargetLocation = this->GetComponentLocation() + (this->GetComponentRotation().Vector() * Range);

	// Save the original location of this component
	OriginalLocation = TargetLocation;

	// Face lasers to target location
	for (int32 i = 0; i < LaserBeams.Num(); i++)
	{
		if (LaserBeams[i].LaserMeshComponent->IsValidLowLevel())
		{

			// Find the laser rotation 
			FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(LaserBeams[i].LaserMeshComponent->GetComponentLocation(), TargetLocation);

			// Set the rotation of the laser to face the target location
			LaserBeams[i].LaserMeshComponent->SetWorldRotation(TargetRotation);


		}

	}

	// Allow scaling of lasers
	bIsScaling = true;
}

// Destroy this component and all its associated children components
void ULaserComponent::DestroyThis() 
{
	// Play sound
	if (HitTarget->IsValidLowLevel())
	{
		HitTarget->Destroy();
	}

	// Get all children components and destroy them
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	// Destroy all children to ensure we don't get orphaned objects in the world
	for (int32 i = 0; i < Children.Num(); i++)
	{
		if (Children[i]->IsValidLowLevel())
		{
			Children[i]->DestroyComponent(false);
		}
	}

	// Destroy itself
	if (this->IsValidLowLevel())
	{
		this->DestroyComponent();
	}
}


// Iterate through all laser beams and set custom properties
void ULaserComponent::GenerateLasers()
{
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
