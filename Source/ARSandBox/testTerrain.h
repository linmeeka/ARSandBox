// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"
#include "ReliefMap.h"
#include "ImageProcessor.h"
#include "FuildSpawner.h"
#include "CollisionSpawner.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshObjectBase.h"
#include "testTerrain.generated.h"

/**
 * 
 */
class ACollisionSpawner;
UCLASS()
class ARSANDBOX_API AtestTerrain : public ARuntimeMeshObjectBase
{
	GENERATED_BODY()

// terrain

private:
	
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FRuntimeMeshTangent> Tangents;
	TArray<FColor> VertexColors;
	TArray<FVector2D> TextureCoordinates;
	TArray<int32> Triangles;
	
	bool bGenerated;
	FBox BoundingBox;

public:
	// Sets default values for this actor's properties
	AtestTerrain(); 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	void OnConstruction(const FTransform& Transform) override;
	void Generate();
	int flagC = 0;
	float CellSize = 1;
	float scalingFactor = 10;
	float Height = 20;


// relief map
private:
	int depthScale = 1;

	int sumNumber = 409600;

	UMaterial *terrainMaterial;
	UMaterialInstanceDynamic *DynamicMaterial;
	void initMaterial();

	ReliefMap *reliefMapSpawner=new ReliefMap();

// counter
	TArray<int> counterFlag;


//fluid
	ACollisionSpawner *collisionSpawner = new ACollisionSpawner();

	const int basinTreshold = 40;
//	void setCollisionBody();

	TArray<FVector> verticesLow, verticesHigh;
//	void spawnFuild();
	AFuildSpawner *fuildSpawner;

//Filter
	AImageProcessor *imageProcessor = new AImageProcessor();

//test
	void setCircle(int i, int j, int tmp);
	void setTestDepthValue();
	int calLength(int x, int y);

	void setEdge();

	void calDepthSumPoint(int threshold);

	//counter
	const int counterNumber = 10;
	int minDepthValue, maxDepthValue;
	TArray<int> counterValue;
	int realHeight = 480;

public:
	void clearCollisionBody();
	void addCollisionBody(const TArray<FVector> &presentCollisionBody);

public:
	TArray<FColor> &getColor()
	{
		return VertexColors;
	}

	void updateMeshTerrain(const DepthFrame &depthFrame);
};
