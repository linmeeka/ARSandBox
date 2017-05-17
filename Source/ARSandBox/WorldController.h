// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"
#include "DrawDepthMap.h"
#include "depthFrameGetter.h"
#include "ReliefMap.h"
#include "ImageProcessor.h"
#include "FuildSpawner.h"
#include "CollisionSpawner.h"
#include "meshTerrain.h"
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
	AdepthFrameGetter *depthFrameGetter;
	void getDepthFrameGetter();

	//Filter
	AImageProcessor *imageProcessor = new AImageProcessor();

	//reliefMap
	ReliefMap *reliefMapSpawner = new ReliefMap();

	// meshTerrain
	AmeshTerrain *meshTerrain;
	void getMeshTerrain();

	//collision
	ACollisionSpawner *collisionSpawner = new ACollisionSpawner();
	void setCollisionBody();

	//fuild
	void spawnFuild();
	void getFuildSpawner();
	AFuildSpawner *fuildSpawner;
	const int basinTreshold = 40;

	//drawDepthMap
	ADrawDepthMap *drawDepthMap;
	void getDrawDepthMap();

	//debugLog
	void logMessage(int message);
};
