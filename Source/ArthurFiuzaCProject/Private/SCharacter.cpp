// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "DrawDebugHelpers.h"
#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SAttributeComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotation View
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	//Offset to the right pawn
	LineStart += GetActorRightVector() * 100.0f;
	//Set Line end in direction of the actor forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	//Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	//Draw Controller Rotation
	DrawDebugDirectionalArrow(GetWorld(),LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);


	//DrawDebugDirectionalArrow()
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	FVector RightVector =  FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ASCharacter::setTarget()
{
	//Hit point
	CamLocation = CameraComp->GetComponentLocation();
	CamRotation = CameraComp->GetComponentRotation();
	FCollisionObjectQueryParams ObjectQuerryParams;
	CamEnd = CamLocation + (CamRotation.Vector() * 10000);
	FHitResult hit;
	bool Ishit = GetWorld()->LineTraceSingleByObjectType(hit, CamLocation, CamEnd, ObjectQuerryParams);

	CamPoint = Ishit ? hit.ImpactPoint : CamEnd;


	//debug
	//DrawDebugLine(GetWorld(), CamLocation, CamEnd, FColor::Purple , false, 2.0f, 0, 2.0f);
	DrawDebugSphere(GetWorld(), hit.ImpactPoint, 30.0f, 32, FColor::Purple, false, 2.0f);

}

void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensure(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

// 		FCollisionObjectQueryParams ObjParams;
// 		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
// 		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
// 		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FRotator ProjDir = (CamPoint - HandLocation).Rotation();

		FTransform SpawnTM = FTransform(ProjDir, HandLocation);

		


		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	setTarget();

	
	//Spawn projectile function
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}


void ASCharacter::UltimateAttack()
{
	PlayAnimMontage(AttackAnim);

	setTarget();

	//Spawn projectile function
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::UltimateAttack_TimeElapsed, 0.2f);

}

void ASCharacter::UltimateAttack_TimeElapsed()
{

	SpawnProjectile(UltimateClass);
}


void ASCharacter::TeleportAttack()
{
	PlayAnimMontage(AttackAnim);

	setTarget();

	//Spawn projectile function
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::TeleportAttack_TimeElapsed, 0.2f);

}

void ASCharacter::TeleportAttack_TimeElapsed()
{

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	SpawnProjectile(ProjectileTPClass);
}

void ASCharacter::TeleportPortal()
{

}

void ASCharacter::PlayerJump()
{
	this->Jump();
}


// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &ASCharacter::UltimateAttack);
	
	PlayerInputComponent->BindAction("TeleportAttack", IE_Pressed, this, &ASCharacter::TeleportAttack);


	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &ASCharacter::PlayerJump);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
	
}


