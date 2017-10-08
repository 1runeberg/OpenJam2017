// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ATarget.h"
#include "LaserComponent.generated.h"

USTRUCT(BlueprintType)
struct FLaser
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UStaticMesh* LaserMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UMaterialInterface* LaserMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FTransform TransformOffset;

	UStaticMeshComponent* LaserMeshComponent;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENJAM2017_API ULaserComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULaserComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	TArray<FLaser> LaserBeams;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector LaserScaleFactor = FVector(0.1,0.f,0.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector LaserShrinkFactor = FVector(0.5, 0.f, 0.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	float Range = 1000.f;

	UFUNCTION(BlueprintCallable, Category = "VR")
	void FireLasers();

	UFUNCTION(BlueprintCallable, Category = "VR")
	void GenerateLasers();

private:
	bool bIsScaling = false;
	bool bIsShrinking = false;
	AATarget* HitTarget;

	FVector OriginalLocation = FVector::ZeroVector;
	void DestroyThis();
};
