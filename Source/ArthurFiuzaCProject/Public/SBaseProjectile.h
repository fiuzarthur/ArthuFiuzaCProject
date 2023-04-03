// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"


class UParticleSystemComponent; 
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()//ABSTRACT
class ARTHURFIUZACPROJECT_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") 
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") 
	 UParticleSystemComponent* EffectComp;
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); 
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override; 

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;

public:	
// 	Called every frame
// 	virtual void Tick(float DeltaTime) override;
// Sets default values for this actor's properties
	ASBaseProjectile();

};
