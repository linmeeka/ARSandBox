// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"
#include "GameFramework/Actor.h"
#include "FuildSpawner.generated.h"

UCLASS()
class ARSANDBOX_API AFuildSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuildSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UParticleSystem* TestParticle;
	UParticleSystemComponent* LastPSC;
	
	bool initFlag = false;
	void loadParticle();

//check position
	TMap<int, int> depthPointCount;;
	TMap<int, int> intervalPointCount;
	const int planeThreshold = 10;
	int planeCount;

public:	
	int planeDepth;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void spawnFuild(FTransform spawnTransform);
	void destoryFuild();
	void calPlaneDepth(const DepthFrame &depthFrame);
	void initFuild();
};
