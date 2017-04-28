// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "testTerrain.h"
#include "ParallelFor.h"

struct FConstructorStatics
{
	ConstructorHelpers::FObjectFinderOptional<UMaterial> MaterialFinder;
	FConstructorStatics()
		:  MaterialFinder(TEXT("Material'/Game/testMaterial.testMaterial'"))
	{
	}
};

static FConstructorStatics ConstructorStatics;

AtestTerrain::AtestTerrain():bGenerated(false)
{
	PrimaryActorTick.bCanEverTick = true;
	RuntimeMesh->bUseComplexAsSimpleCollision = false;
	terrainMaterial = ConstructorStatics.MaterialFinder.Get();
}

void AtestTerrain::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add(TEXT("MeshTerrain"));
	initMaterial();
//	initColor();
	
}

void AtestTerrain::initMaterial()
{
	RuntimeMesh->SetMaterial(0,terrainMaterial);
}

void AtestTerrain::Generate()
{
	BoundingBox = FBox(FVector(-HalfLength * CellSize, -HalfWidth * CellSize, -100), FVector(HalfLength * CellSize, HalfWidth * CellSize, 100));

	float Scale = CellSize / scalingFactor;

	for (int32 YIndex = -HalfWidth; YIndex < HalfWidth; YIndex++)
	{
		for (int32 XIndex = -HalfLength; XIndex < HalfLength; XIndex++)
		{
			Vertices.Add(FVector(XIndex * CellSize, YIndex * CellSize, 0));
			Normals.Add(FVector(0, 0, 1));
			Tangents.Add(FRuntimeMeshTangent(-1, 0, 0));
			VertexColors.Add((FColor::Orange));
			TextureCoordinates.Add(FVector2D(XIndex * Scale, YIndex * Scale));
		}
	}

	URuntimeMeshLibrary::CreateGridMeshTriangles(HalfLength * 2, HalfWidth * 2, true, Triangles);

//	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents);
	// 加碰撞体
	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents, false, EUpdateFrequency::Frequent);
//	RuntimeMesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, VertexColors, Tangents, true);
	bGenerated = true;
}

void AtestTerrain::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
//
//	if (!bGenerated)
//		Generate();
//
//	getDepthValue();
//	imageProcessor->imageFiltering(depthValue);
////	
////	setTestDepthValue();
////	reliefMapSpawner->setVertexColorsByThreshold(VertexColors, depthValue);
//	reliefMapSpawner->setVertexColorsByGradient(VertexColors,depthValue);
//	reliefMapSpawner->drawCounter(VertexColors, depthValue);
////	updateColorVertex();
////	drawContour();
////	setEdge();
//	calDepthSumPoint(250);
//
//	for (int i = 0; i < mapLength; i++)
//	{
//		for (int j = 0; j < mapWidth; j++)
//		{
//			float Scale = CellSize / scalingFactor;
//			int index = i*mapWidth + j;
//			Vertices[index].Z = depthValue[index] * Scale;
//		}
//	}
//
//	flagC++;
////	if(flagC==50)
//	if (flagC % 20 == 0)
//	{
//		setCollisionBody();
//		spawnFuild();
//	}
//	
//	/*
//	if (flagC==50)
//		spawnFuild();
//	if (flagC == 100)
//		fuildSpawner->destoryFuild();*/
//	
//	RuntimeMesh->UpdateMeshSection(0, Vertices, Normals, TextureCoordinates, VertexColors, Tangents);
}

void AtestTerrain::updateMeshTerrain(const DepthFrame &depthFrame)
{
	if (!bGenerated)
		Generate();

//	calDepthSumPoint(250);

	for (int i = 0; i < depthFrame.mapLength; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			float Scale = CellSize / scalingFactor;
			int index = i*depthFrame.mapWidth + j;
			Vertices[index].Z = depthFrame.depthValue[index] * Scale;
		}
	}

	//flagC++;
	////	if(flagC==50)
	//if (flagC % 20 == 0)
	//{
	//	setCollisionBody();
	//	spawnFuild();
	//}

	///*
	//if (flagC==50)
	//spawnFuild();
	//if (flagC == 100)
	//fuildSpawner->destoryFuild();*/

	//RuntimeMesh->UpdateMeshSection(0, Vertices, Normals, TextureCoordinates, VertexColors, Tangents);
}

//void AtestTerrain::setCollisionBody()
//{
//	RuntimeMesh->ClearCollisionConvexMeshes();
//	collisionSpawner->setEdgeColor(VertexColors);
//	collisionSpawner->setCollision(mapLength, mapWidth, depthValue);
// 	int listSize = collisionSpawner->collisionBodyList.Num();
//	for (int i = 0; i < listSize; i++)
//	{
//		TArray<FVector>presentCollisionBody;
//		presentCollisionBody.Empty();
//		presentCollisionBody.Add(collisionSpawner->collisionBodyList[i].button);
//		presentCollisionBody.Add(collisionSpawner->collisionBodyList[i].top);
//		presentCollisionBody.Add(collisionSpawner->collisionBodyList[i].right);
//		presentCollisionBody.Add(collisionSpawner->collisionBodyList[i].left);
//		presentCollisionBody.Add(collisionSpawner->collisionBodyList[i].center);
//		RuntimeMesh->AddCollisionConvexMesh(presentCollisionBody);
//	}
//}

void AtestTerrain::addCollisionBody(const TArray<FVector> &presentCollisionBody)
{
	RuntimeMesh->AddCollisionConvexMesh(presentCollisionBody);
}

void AtestTerrain::clearCollisionBody()
{
	RuntimeMesh->ClearCollisionConvexMeshes();
}

void AtestTerrain::OnConstruction(const FTransform& Transform)
{
	Generate();
}

//fuild
//void AtestTerrain::spawnFuild()
//{
//	TArray<AActor*> actorList;
//	TSubclassOf<AFuildSpawner> classToFind;
//	classToFind = AFuildSpawner::StaticClass();
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorList);
//
//	for (int i = 0; i < actorList.Num(); i++)
//	{
//		if (actorList[i]->Tags[0] == TEXT("FuildSpawnerTag"))
//		{
//			fuildSpawner = Cast<AFuildSpawner>(actorList[i]);
//		}
//	}
//
//	fuildSpawner->calPlaneDepth(depthValue);
//
//	if (fuildSpawner->planeDepth < 20)
//	{
//		return;
//	}
//	int spawnNumber = -1;
//	int spawnArea = 0;
//	for (int i = 0; i < collisionSpawner->collisionBodyList.Num(); i++)
//	{
//		int nowDepth = collisionSpawner->collisionBodyList[i].center.Z;
//		if (nowDepth < fuildSpawner->planeDepth-basinTreshold)
//		{
//			if (collisionSpawner->collisionBodyList[i].sumPoint>=spawnArea)
//			{
//				spawnArea = collisionSpawner->collisionBodyList[i].sumPoint;
//				spawnNumber = i;
//			}
//		}
//	}
//	if (spawnNumber != -1)
//	{
//		FTransform spawnTransform;
//		spawnTransform.SetLocation(collisionSpawner->collisionBodyList[spawnNumber].center);
//		spawnTransform.SetRotation(FQuat(90, 0, 0, 1));
//		fuildSpawner->spawnFuild(spawnTransform);
//	}
//}

// test

void AtestTerrain::setEdge()
{
	for (int i = 0; i < mapLength; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (VertexColors[i*mapWidth + j] != FColor::Black)
				VertexColors[i*mapWidth + j] = FColor::White;
		}
	}
}

int AtestTerrain::calLength(int x, int y)
{
	return (x - 240)*(x - 240) + (y - 320)*(y - 320);
}

void AtestTerrain::setTestDepthValue()
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

void AtestTerrain::setCircle(int i, int j, int tmp)
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

void AtestTerrain::calDepthSumPoint(int threshold)
{
	int sum = 0;
	for (int i = 0; i < sumNumber; i++)
	{
//		if (depthValue[i] >= threshold)
		if(VertexColors[i]==FColor::Black)
			sum++;
	}
	FString logSumNumber;
	logSumNumber = FString::FromInt(sum);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, logSumNumber);
}
