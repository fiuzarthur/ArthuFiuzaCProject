// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosive.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
ASExplosive::ASExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosive::AOnActorHit);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	RootComponent = MeshComp;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->Radius = 500;
	RadialForce->SetupAttachment(MeshComp);



}

void ASExplosive::AOnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->ActorHasTag("Projectile"))
	{
		RadialForce->ImpulseStrength = 2000;
		RadialForce->bImpulseVelChange = true;
		RadialForce->FireImpulse();

		this->Destroy();
	}

}


// Called when the game starts or when spawned
void ASExplosive::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

