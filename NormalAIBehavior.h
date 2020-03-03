// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NormalAIBehavior.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POSTGAME2_API UNormalAIBehavior : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNormalAIBehavior();
	
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float health;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float exp;

    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        float damage;
    
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


    void setAI() {
        damage;
        health;
        exp;
    }

    UFUNCTION(Category = Gameplay, BlueprintCallable)
    bool kill() {
        if (health == 0 || damage >= health) {
            return true;
        }
        else if (health >= 1 || damage < health) {
            return false;
        }
        else {
            return false;
        }
    }

    UFUNCTION(Category = Gameplay, BlueprintCallable)
    bool hit() {
        if (true) {
            health = health - damage;
        }
        else if (false) {
            return 100;
        }
        else
            return 102;
    }

    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
        class USoundBase* Walking;

    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
        class USoundBase* Tossing;

    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
        class USoundBase* Hitting;

	static const FName MoveForwardBinding;
	static const FName MoveSidewaysBinding;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
