// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ATarget.generated.h"

UCLASS()
class OPENJAM2017_API AATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UStaticMesh* OuterShell;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UStaticMesh* InnerShell;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UMaterialInterface* OuterShellMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UMaterialInterface* InnerShellMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector OuterShellScale = FVector(1.f, 1.f ,1.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector InnerShellScale = FVector(1.f, 1.f, 1.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector GravityVelocity = FVector(0.f, 0.f, -1.f);

	/** Apply target variables for when called from an external class */
	void ApplyTargetVars();

	USphereComponent* SphereCollision;
	UStaticMeshComponent* OuterShellComponent;
	UStaticMeshComponent* InnerShellComponent;
};
