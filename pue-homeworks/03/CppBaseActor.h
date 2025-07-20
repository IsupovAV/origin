// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppBaseActor.generated.h"

UCLASS()
class CPPBASE_API ACppBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  //UPROPERTY(VisibleAnywhere);
  //FString PlayerName = "Netologiya";

  //UPROPERTY(EditAnywhere);
  //int EnemyNum = 20;
  //
  //UPROPERTY(EditDefaultsOnly);
  //float CurrentHealth = 57.54687;

  //UPROPERTY(EditInstanceOnly);
  //bool IsAlive = true;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Info")
  int32 EnemyNum = 0;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Info")
  bool IsAlive = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
  void const ShowActorInformation();

};
