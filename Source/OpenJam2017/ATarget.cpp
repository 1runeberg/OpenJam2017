// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#include "ATarget.h"


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
	
	// Create Actor's outer shell
	if (OuterShell->IsValidLowLevel())
	{
		OuterShellComponent = NewObject<UStaticMeshComponent>(this);
		OuterShellComponent->RegisterComponentWithWorld(GetWorld());
		OuterShellComponent->SetMobility(EComponentMobility::Movable);
		OuterShellComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		OuterShellComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		OuterShellComponent->SetStaticMesh(OuterShell);

		if (OuterShellMaterial->IsValidLowLevel())
		{
			OuterShellComponent->SetMaterial(0, OuterShellMaterial);
		}
	}

	// Create Actor's inner shell
	if (InnerShell->IsValidLowLevel())
	{
		InnerShellComponent = NewObject<UStaticMeshComponent>(this);
		InnerShellComponent->RegisterComponentWithWorld(GetWorld());
		InnerShellComponent->SetMobility(EComponentMobility::Movable);
		InnerShellComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		InnerShellComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InnerShellComponent->SetStaticMesh(InnerShell);

		if (InnerShellMaterial->IsValidLowLevel())
		{
			InnerShellComponent->SetMaterial(0, InnerShellMaterial);
		}
	}
}

// Called every frame
void AATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

