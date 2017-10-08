// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetGenerator.generated.h"

USTRUCT(BlueprintType)
struct FTargetVars
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UStaticMesh* OuterShell;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UStaticMesh* InnerShell;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UMaterialInterface* OuterShellMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	UMaterialInterface* InnerShellMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector OuterShellScale = FVector(1.f, 1.f, 1.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector InnerShellScale = FVector(1.f, 1.f, 1.f);

};

UCLASS()
class OPENJAM2017_API ATargetGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FTargetVars TargetVars;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector MinOffset = FVector(-100.f, -100.f, -10.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	FVector MaxOffset = FVector(100.f, 100.f, 10.f);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VR")
	float SpawnInterval = 1.f;

private:
	FTimerHandle TimerHandle;

	void SpawnTarget();
};
