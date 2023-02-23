// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosive.generated.h"

class UMeshComponent;
class URadialForceComponent;

UCLASS()
class ARTHURFIUZACPROJECT_API ASExplosive : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASExplosive();

protected:

	UPROPERTY(VisibleAnywhere)
	UMeshComponent* MeshComp;


	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForce;



	UFUNCTION()
	void AOnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
