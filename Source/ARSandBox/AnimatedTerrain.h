// Copyright 2016 Chris Conway (Koderz). All Rights Reserved.

#pragma once

//#include "ReliefMapTexture.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshObjectBase.h"
#include "AnimatedTerrain.generated.h"

UCLASS()
class ARSANDBOX_API AAnimatedTerrain : public ARuntimeMeshObjectBase
{
	GENERATED_BODY()

//public:
//	//AReliefMapTexture textureMaker;
//
//public:
//	void initTexture();
//	void initMaterial();
//	void updateMeterial();
//	FString materialName;
//	UMaterial *terrainMaterial;
//	UTexture *reliefMapTexture1;
//	UTexture2D *reliefMapTexture;
//	UMaterialInstanceDynamic *DynamicMaterial;
//
//public:
//	bool bGenerated;
//	FBox BoundingBox;
//
//	// Sets default values for this actor's properties
//	AAnimatedTerrain();
//
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//	// Called every frame
//	virtual void Tick(float DeltaSeconds) override;
//
//	void OnConstruction(const FTransform& Transform) override;
//
//	void Generate();
//
//	float AnimationOffsetX = 0.0f;
//	float AnimationOffsetY = 0.0f;
//
//	// int32 HalfWidth = 400;
//
//
//	int flagC = 0;
//
//	float CellSize = 1;
//	float scalingFactor = 10;
//	float Height = 20;
//
//	//test
//	void setCircle(int i, int j, int tmp);
//	void setTestDepthValue();
//	int calLength(int x, int y);
//
//// relief map
//	int sumNumber = 409600;
//	void updateTextureMethod();
//////基础绘制;
//	UPROPERTY(EditAnywhere) TArray<FColor> colorValue;
//
//	//地形图
//	TArray<int> value_interval;
//	TArray<FColor> color_interval;
//
//
//	void updateTextureColor();
//	void initColor();
//	void setTexture();
//
//	//等高线
//	TArray<int> counterFlag;
//
//	void drawContour();
//	bool checkCounter(int x, int y);
//	bool checkCoordinate(int x, int y);
public:
	bool bGenerated;
	FBox BoundingBox;

	// Sets default values for this actor's properties
	AAnimatedTerrain();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void OnConstruction(const FTransform& Transform) override;

	void Generate();

	float AnimationOffsetX = 0.0f;
	float AnimationOffsetY = 0.0f;

	//int32 HalfWidth = 400;
	int32 HalfWidth = 240;

	float CellSize = 5;
	float Height = 20;

	int cnt = 0;


};
