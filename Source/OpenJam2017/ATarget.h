// Copyright 2017 runeberg.io under the MIT OpenSource License Terms

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

private:
	UStaticMeshComponent* OuterShellComponent;
	UStaticMeshComponent* InnerShellComponent;
};
