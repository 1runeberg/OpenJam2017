// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#include "TargetGenerator.h"
#include "ATarget.h"


// Sets default values
ATargetGenerator::ATargetGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	// Call the timed job
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATargetGenerator::SpawnTarget, SpawnInterval, true);
}

// Called every frame
void ATargetGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Spawn targets into the world
void ATargetGenerator::SpawnTarget()
{
	// Generate a random target location
	FVector TargetLocation = GetActorLocation() + FVector(FMath::RandRange(MinOffset.X, MaxOffset.X),
		FMath::RandRange(MinOffset.Y, MaxOffset.Y),
		FMath::RandRange(MinOffset.Z, MaxOffset.Z));

	// Spawn target
	AATarget* NewTarget = GetWorld()->SpawnActor<AATarget>(AATarget::StaticClass(), TargetLocation, FRotator::ZeroRotator);
	if (NewTarget->IsValidLowLevel())
	{	
		// Set target vars
		NewTarget->InnerShell = TargetVars.InnerShell;
		NewTarget->OuterShell = TargetVars.OuterShell;
		NewTarget->OuterShellMaterial = TargetVars.OuterShellMaterial;
		NewTarget->InnerShellMaterial = TargetVars.InnerShellMaterial;
		NewTarget->OuterShellScale = TargetVars.OuterShellScale;
		NewTarget->InnerShellScale = TargetVars.InnerShellScale;
		NewTarget->SoundFX = TargetVars.SoundFX;

		// Apply target vars
		NewTarget->ApplyTargetVars();

		// Postion target
		if (NewTarget->OuterShellComponent->IsValidLowLevel())
		{
			NewTarget->OuterShellComponent->SetWorldLocation(TargetLocation);
		}

		if (NewTarget->InnerShellComponent->IsValidLowLevel())
		{
			NewTarget->InnerShellComponent->SetWorldLocation(TargetLocation);
		}

		if (NewTarget->SphereCollision->IsValidLowLevel())
		{
			NewTarget->SphereCollision->SetWorldLocation(TargetLocation);
		}

		UE_LOG(LogTemp, Warning, TEXT("TargetLocation is %s"), *TargetLocation.ToString());

	}

}
