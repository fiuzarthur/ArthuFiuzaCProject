// Fill out your copyright notice in the Description page of Project Settings.


#include "SSpawner.h"

#include "Components/TextRenderComponent.h"

// Sets default values
ASSpawner::ASSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeToSpawn = FMath::FRandRange(.1, 5);
	SpawnTimer = 0.0f;
	GameTimer = 0;
	BarrelNum = 1;
	BarrelType = 0;
	Spawning = false;

	SceneC1 = CreateDefaultSubobject<USceneComponent>("Scene1");
	RootComponent = SceneC1;

	SceneC2 = CreateDefaultSubobject<USceneComponent>("Scene2");
	SceneC2->AttachTo(RootComponent);

	SceneC3 = CreateDefaultSubobject<USceneComponent>("Scene3");
	SceneC3->AttachTo(RootComponent);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>("Text");
	TextRender->AttachTo(RootComponent);

	


}

// Called when the game starts or when spawned
void ASSpawner::BeginPlay()
{
	Super::BeginPlay();
	Spawning = true;
	GameTimer = TimeMax;
	TextRender->SetText(FString::FromInt(GameTimer) + " segundos");
	GetWorldTimerManager().SetTimer(timeHandler, this, &ASSpawner::UpdateTime, 1.0f, true, 0.0f);
	
}

// Called every frame
void ASSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	int randItem = FMath::RandRange(0, 1);
	if(Spawning)
	{
		SpawnTimer += DeltaTime;

		if(SpawnTimer >= TimeToSpawn)
		{
			BarrelNum = FMath::RandRange(1, 3);
			BarrelType = FMath::RandRange(0, 1);
			FTransform SpawnTM;

			if(BarrelNum == 1)
			{
				SpawnTM = FTransform(SceneC1->GetComponentTransform());
			}else if(BarrelNum == 2)
			{
				SpawnTM = FTransform(SceneC2->GetComponentTransform());
			}else
			{
				SpawnTM = FTransform(SceneC3->GetComponentTransform());
			}

			FActorSpawnParameters SpawnParams;

			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			if(BarrelType == 0)
			{
				GetWorld()->SpawnActor<AActor>(NormalB, SpawnTM, SpawnParams);
			}else
			{
				GetWorld()->SpawnActor<AActor>(ExplosiveB, SpawnTM, SpawnParams);
			}

			TimeToSpawn = FMath::FRandRange(.1, 5);
			SpawnTimer = 0.0f;
		}
	}
}

void ASSpawner::UpdateTime()
{
	GameTimer--;
	TextRender->SetText(FString::FromInt(GameTimer) + " segundos");

	if (GameTimer == 0)
	{
		Spawning = false;
		TextRender->SetText("Game Over");

		TArray<AActor*> LeftBarrels;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ExplosiveB, LeftBarrels);

		for (auto Barrel : LeftBarrels)
		{
			Barrel->Destroy();
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), NormalB, LeftBarrels);

		for (auto Barrel : LeftBarrels)
		{
			Barrel->Destroy();
		}

		GetWorldTimerManager().ClearTimer(timeHandler);
		
	}
}


