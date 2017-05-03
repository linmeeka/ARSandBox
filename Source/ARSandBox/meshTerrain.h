// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RuntimeMeshObjectBase.h"
#include "meshTerrain.generated.h"

/**
 * 
 */
UCLASS()
class ARSANDBOX_API AmeshTerrain : public ARuntimeMeshObjectBase
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
	AmeshTerrain();
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

//size
	int mapWidth = 640;
	int mapHeight = 640;
	const int mapLength = 640;
	const int HalfWidth = 320;
	const int HalfLength = 320;

	// relief map
private:
	UMaterial *terrainMaterial;
	UMaterialInstanceDynamic *DynamicMaterial;
	void initMaterial();


public:
	void clearCollisionBody();
	void addCollisionBody(const TArray<FVector> &presentCollisionBody);

public:
	TArray<FColor> &getColor()
	{
		return VertexColors;
	}

	void updateMeshTerrain(const DepthFrame &depthFrame);

	//test
	void setCircle(int i, int j, int tmp);
	void setTestDepthValue();
	int calLength(int x, int y);
	void setEdge();
	void calDepthSumPoint(int threshold);
};
