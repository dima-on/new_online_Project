#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "C_PLayer.generated.h"

UCLASS()
class NEW_ONLINE_API AC_PLayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_PLayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UCapsuleComponent* main_body;
	UCameraComponent* main_camera;

	UFUNCTION(BlueprintCallable)
	void set_start_data(
		UCapsuleComponent* main_body_sd,
		UCameraComponent* main_camera_sd
	);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HP = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float new_Damage = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ActiveWearpone = 0;

	UFUNCTION(BlueprintCallable)
	void movement(float DeltaTime, float val, float val_rl, float speed);

	UFUNCTION(BlueprintCallable)
	void camera_move(float DeltaTime, float MouseX, float MouseY, float sensetive);

	UFUNCTION(BlueprintCallable)
	void jump(float force);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintImplementableEvent)
	void Died_char();

	UFUNCTION(BlueprintImplementableEvent)
	void Apply_Damage_BP(float Damage);

	UFUNCTION(BlueprintImplementableEvent)
	void Get_Distance_Damage(int Index_Wearpon, float Distance);



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetDamage(float Damage);
};
