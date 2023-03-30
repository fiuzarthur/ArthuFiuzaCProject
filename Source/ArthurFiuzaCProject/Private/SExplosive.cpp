// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosive.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

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

	/*
	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->Radius = 500;
	RadialForce->SetupAttachment(MeshComp);
	*/


}

void ASExplosive::AOnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->ActorHasTag("Projectile"))
	{
		/*
		RadialForce->ImpulseStrength = 2000;
		RadialForce->bImpulseVelChange = true;
		RadialForce->FireImpulse();
		*/

		destroyByPlayer = true;
		this->Destroy();

		//debug
		//UE_LOG(LogTemp, Log, TEXT("OnActorHit ActorHasTag -Projectile- Explosive Barrel "))

	}

	//%s = string
	//%f = float
	// logs: "OtherActor: MyActor_1, at game time: 124.4"

	//debug
	//UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	//FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	//DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
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

