// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h" 
#include "Kismet/GameplayStatics.h" 
#include "Particles/ParticleSystemComponent.h" 
#include "Components/SphereComponent.h" 

// Sets default values
ASBaseProjectile::ASBaseProjectile()
{

	
//  	Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 		PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ASBaseProjectile::OnActorHit);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 8000;

}
// Called when the game starts or when spawned
// void ASBaseProjectile::BeginPlay()
// {
// 	Super::BeginPlay();
// 	
// }

void ASBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor && OtherActor != GetInstigator())
	{
		Explode();
	}
}

// Called every frame
// void ASBaseProjectile::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// 
// }

// _Implement from it being marked as BlueprintNativeEvent

void ASBaseProjectile::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		Destroy();
	}
}



void ASBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



