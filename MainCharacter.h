// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainCharacter.generated.h"


UCLASS()
class POSTGAME2_API AMainCharacter : public AActor
{
	GENERATED_BODY()

    UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MainCharacter;

    UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComponent;

    UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

public:	
	// Sets default values for this actor's properties
	AMainCharacter();

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float MoveSpeed;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        double Scarespeed;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float health;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float exp;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float damage;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float defence;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float scared;


	UPROPERTY(VisibleAnywhere, Category= "Percy")
		UStaticMeshComponent* StaticMesh;
	
	UFUNCTION(Category = Gameplay, BlueprintCallable)
        float getHealth() {
        return health;
    }

    UFUNCTION(Category = Gameplay, BlueprintCallable)
    float getExp() {
        return exp;
    }

    UFUNCTION(Category = Gameplay, BlueprintCallable)
    float getDamage() {
        return damage;
    }

    UFUNCTION(Category = Gameplay, BlueprintCallable)
    float getDefence() {
        return defence;
    }

    UFUNCTION(Category = Gameplay, BlueprintCallable)
    float getScared() {
        return scared;
    }

    void fearLevel(float scare) {
            scared = scare;
            bool hit;
            while(hit == true) {
                scare = scare + 1;
                while (scare <= 1 && scare == 100.0) {
                   MoveSpeed = scare * MoveSpeed * Scarespeed;
                }
            }
    }

    void setPlayer() {
        health;
        damage;
        defence;
        exp;
        scared;
    }

    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
        class USoundBase* Walking;

    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
        class USoundBase* Tossing;

    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
        class USoundBase* Hitting;

    virtual void Tick(float DeltaSeconds) override;


	static const FName MoveForwardBinding;
	static const FName MoveSidewaysBinding;

private:
	uint32 bCanToss : 1;
	FTimerHandle TimerHandle_TossTimerExpired;
    std::string _weapon;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //FORCEINLINE class UInputComponent* SetupPlayerInputComponent() const { return PlayerInputComponent; }

    void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

    /** Returns ShipMeshComponent subobject **/
    FORCEINLINE class UStaticMeshComponent* GetMainCharacterMeshComponent() const { return MainCharacter; }
    /** Returns CameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
