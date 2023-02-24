// Fill out your copyright notice in the Description page of Project Settings.


#include "SSpawner.h"

// Sets default values
ASSpawner::ASSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneC1 = CreateDefaultSubobject<USceneComponent>("Scene1");
	RootComponent = SceneC1;

	SceneC2 = CreateDefaultSubobject<USceneComponent>("Scene2");
	SceneC2->AttachTo(RootComponent);

	SceneC3 = CreateDefaultSubobject<USceneComponent>("Scene3");
	SceneC3->AttachTo(RootComponent);
	


}

// Called when the game starts or when spawned
void ASSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

