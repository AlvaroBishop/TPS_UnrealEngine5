// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Gun.h"
#include "Math/UnitConversion.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass); // Spawn actor
	GetMesh()-> HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); // we hide the weapon in the sekeleton
	// We attach the component to the weapon socket
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules ::KeepRelativeTransform, TEXT("WeaponSocket"));
	// allows the gun to know what is the owning character
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this,  &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed,this, &AShooterCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AShooterCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	// UE_LOG(LogTemp, Display, TEXT("Velocity: %f"), AxisValue * (bShiftPressed ? 1.0f : 0.42f));
	AddMovementInput(GetActorForwardVector() * AxisValue * (bShiftPressed ? 1.0f : 0.42f));

	
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	// UE_LOG(LogTemp, Display, TEXT("Move Right2: %f"), AxisValue * (bShiftPressed ? 1.0f : 0.42f));
	AddMovementInput(GetActorRightVector() * AxisValue * (bShiftPressed ? 1.0f : 0.42f));
	
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}


void AShooterCharacter::Run()
{
	bShiftPressed = !bShiftPressed;
}






