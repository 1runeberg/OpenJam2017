// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#include "LaserComponent.h"


// Sets default values for this component's properties
ULaserComponent::ULaserComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	// ...
}

