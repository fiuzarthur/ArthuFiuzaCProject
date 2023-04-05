// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundCue;
UCLASS()
class ARTHURFIUZACPROJECT_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:

	
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageAmount = 0;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundCue* TraceLoopSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundCue* ImpactSound;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* AudioComp;
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	//void Explode();

	virtual void PostInitializeComponents() override;

	virtual void Destroyed() override;

	//int32 CallTracker = 3;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TimerFunction();

	FTimerHandle TimerHandle;

};
