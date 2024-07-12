// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PLayer.h"

// Sets default values
AC_PLayer::AC_PLayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_PLayer::BeginPlay()
{
	Super::BeginPlay();

}

void AC_PLayer::set_start_data(UCapsuleComponent* main_body_sd, UCameraComponent* main_camera_sd)
{
	main_body = main_body_sd;
	main_camera = main_camera_sd;
}

void AC_PLayer::movement(float DeltaTime, float val, float val_rl, float speed)
{

	if (main_body) {
		FVector pos = main_body->GetComponentLocation();
		FVector forward = main_body->GetForwardVector() * val * DeltaTime * speed;
		FVector right = main_body->GetRightVector() * val_rl * DeltaTime * speed;
		main_body->SetWorldLocation(pos + forward + right);
		main_body->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
	}
}

void AC_PLayer::camera_move(float DeltaTime, float MouseX, float MouseY, float sensetive)
{
	if (main_camera) {
		FRotator camera_rot = main_camera->GetComponentRotation();
		FRotator main_rot = main_body->GetComponentRotation();

		camera_rot.Pitch += MouseY * DeltaTime * sensetive;
		main_rot.Yaw += MouseX * DeltaTime * sensetive;
		camera_rot.Yaw = main_rot.Yaw;
		camera_rot.Roll = 0;

		main_camera->SetWorldRotation(camera_rot);
		main_body->SetWorldRotation(main_rot);
	}
}

void AC_PLayer::jump(float force)
{
	main_body->AddImpulse(FVector::UpVector * force);
}

void AC_PLayer::Fire()
{
	if (main_camera) {
		FVector start_pos = main_camera->GetComponentLocation();
		FVector end_pos = start_pos + (main_camera->GetForwardVector() * 1000);

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool isHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			start_pos,
			end_pos,
			ECC_Visibility,
			CollisionParams
		);

		if (isHit) {
			Get_Distance_Damage(ActiveWearpone, HitResult.Distance);
			AActor* HitActor = HitResult.GetActor();
			AC_PLayer* Hit_Player = Cast<AC_PLayer>(HitActor);
			if (Hit_Player != nullptr) {
				Hit_Player->SetDamage(new_Damage);
			}

		}
	}
}


// Called every frame
void AC_PLayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_PLayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_PLayer::SetDamage(float Damage)
{
	this->Apply_Damage_BP(Damage);
	if (HP <= 0) {
		Died_char();
	}

}

