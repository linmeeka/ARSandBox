// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "meshTerrain.h"
#include "ParallelFor.h"

struct FConstructorStatics
{
	ConstructorHelpers::FObjectFinderOptional<UMaterial> MaterialFinder;
	FConstructorStatics()
		: MaterialFinder(TEXT("Material'/Game/reliefMeshMaterial.reliefMeshMaterial'"))
	{
	}
};

static FConstructorStatics ConstructorStatics;

AmeshTerrain::AmeshTerrain() :bGenerated(false)
{
	PrimaryActorTick.bCanEverTick = true;
	RuntimeMesh->bUseComplexAsSimpleCollision = false;
	terrainMaterial = ConstructorStatics.MaterialFinder.Get();
}

void AmeshTerrain::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add(TEXT("MeshTerrain"));
	initMaterial();
	VertexColors.Init(FColor::White, 640 * 640);
}

void AmeshTerrain::initMaterial()
{
	RuntimeMesh->SetMaterial(0, terrainMaterial);
}

void AmeshTerrain::Generate()
{
	BoundingBox = FBox(FVector(-HalfLength * CellSize, -HalfWidth * CellSize, -100), 
		FVector(HalfLength * CellSize, HalfWidth * CellSize,300));

	float Scale = CellSize / scalingFactor;

	for (int32 YIndex = -HalfWidth; YIndex < HalfWidth; YIndex++)
	{
		for (int32 XIndex = -HalfLength; XIndex < HalfLength; XIndex++)
		{
			Vertices.Add(FVector(XIndex * CellSize, YIndex * CellSize, 0));
			Normals.Add(FVector(0, 0, 1));
			Tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
			TextureCoordinates.Add(FVector2D(XIndex * Scale, YIndex * Scale));
		}
	}

	//生成三角面片索引（顶点的索引）
	URuntimeMeshLibrary::CreateGridMeshTriangles(HalfLength * 2, HalfWidth * 2, true, Triangles);

	//	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents);
	// 加碰撞体
	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents, false, EUpdateFrequency::Frequent);
	//	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents, true);
	bGenerated = true;
}

void AmeshTerrain::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AmeshTerrain::updateMeshTerrain(const DepthFrame &depthFrame)
{
	if (!bGenerated)
		Generate();

	for (int i = 0; i < depthFrame.mapHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			float Scale = CellSize / scalingFactor;
			int index = i*depthFrame.mapWidth + j;
			Vertices[index].Z = depthFrame.depthValue[index] * Scale;
		}
	}
	RuntimeMesh->UpdateMeshSection(0, Vertices, Normals, TextureCoordinates, VertexColors, Tangents);
	calDepthSumPoint(depthFrame.depthValue[depthFrame.realSumNumber/2]);
}

void AmeshTerrain::addCollisionBody(const TArray<FVector> &presentCollisionBody)
{
	RuntimeMesh->AddCollisionConvexMesh(presentCollisionBody);
}

void AmeshTerrain::clearCollisionBody()
{
	RuntimeMesh->ClearCollisionConvexMeshes();
}

void AmeshTerrain::OnConstruction(const FTransform& Transform)
{
	Generate();
}
// test

void AmeshTerrain::setEdge()
{
	for (int i = 0; i <mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (VertexColors[i*mapWidth + j] != FColor::Black)
				VertexColors[i*mapWidth + j] = FColor::White;
		}
	}
}

int AmeshTerrain::calLength(int x, int y)
{
	return (x - 240)*(x - 240) + (y - 320)*(y - 320);
}

void AmeshTerrain::setTestDepthValue()
{
	for (int i = 0; i < HalfLength * 2; i++)
	{
		for (int j = 0; j < HalfWidth * 2; j++)
		{
			//depthValue[i*mapWidth + j] = rand() % 255;
			int tmp = calLength(i, j);
			setCircle(i, j, tmp);
		}
	}
}

void AmeshTerrain::setCircle(int i, int j, int tmp)
{
	//	int mapWidth = HalfWidth * 2;
	//设置值为 { 0,25, 50,75, 100,125, 150,175, 200,255, 255 };
	//depthValue[0] = 10;
	//if (tmp < 16000)
	//	depthValue[i*mapWidth + j] = 250;
	//else if (tmp < 32000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 48000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 48000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 64000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 80000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 96000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 112000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 128000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 144000)
	//	depthValue[i*mapWidth + j] = 10;
	//else if (tmp < 160000)
	//	depthValue[i*mapWidth + j] = 10;
}

void AmeshTerrain::calDepthSumPoint(int threshold)
{
	int sum = 0;
	for (auto nowColor : VertexColors)
	{
		//		if (depthValue[i] >= threshold)
		if (nowColor == FColor::Black)
			sum++;
	}
	FString logSumNumber;
	logSumNumber = FString::FromInt(threshold);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, logSumNumber);
}




