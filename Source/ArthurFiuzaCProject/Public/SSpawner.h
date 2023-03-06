// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SSpawner.generated.h"


class USceneComponent;
class UTextRenderComponent;

UCLASS()
class ARTHURFIUZACPROJECT_API ASSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSpawner();

protected:

	float SpawnTimer;
	float TimeToSpawn;
	int GameTimer;
	int BarrelNum;
	int BarrelType;

	UPROPERTY(EditAnywhere)
	int TimeMax = 100;

	FTimerHandle timeHandler;

	bool Spawning;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ExplosiveB;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> NormalB;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneC1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneC2;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneC3;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRender;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateTime();
};
