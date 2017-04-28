// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"
#include "depthFrameGetter.h"
#include "ReliefMap.h"
#include "ImageProcessor.h"
#include "FuildSpawner.h"
#include "CollisionSpawner.h"
#include "testTerrain.h"
#include "GameFramework/Actor.h"
#include "WorldController.generated.h"

UCLASS()
class ARSANDBOX_API AWorldController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void processControl(); 
	int frameCounter;
	bool timeToCollision();
	const int frameInterval = 20;

	//depthFrame
	DepthFrame *depthFrame = new DepthFrame();
	AdepthFrameGetter *depthFrameGetter;
	void getDepthFrame();

	//Filter
	AImageProcessor *imageProcessor = new AImageProcessor();

	//reliefMap
	ReliefMap *reliefMapSpawner = new ReliefMap();

	// meshTerrain
	AtestTerrain *meshTerrain;
	void getTestTerrain();

	//collision
	ACollisionSpawner *collisionSpawner = new ACollisionSpawner();
	void setCollisionBody();

	//fuild
	void spawnFuild();
	AFuildSpawner *fuildSpawner;
	const int basinTreshold = 40;
};
