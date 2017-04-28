// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "AnimatedTerrain.h"
#include "RuntimeMeshLibrary.h"
#include "ParallelFor.h"

struct FConstructorStatics
{
	ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;
	ConstructorHelpers::FObjectFinderOptional<UMaterial> MaterialFinder;
	FConstructorStatics()
		: TextureFinder(TEXT("Texture2D'/Game/TestPackages/Flex/flexBaconTex.flexBaconTex'"))
		, MaterialFinder(TEXT("Material'/Game/testMaterial.testMaterial'"))
	{
	}
};

static FConstructorStatics ConstructorStatics;	

// Sets default values
AAnimatedTerrain::AAnimatedTerrain() : bGenerated(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RuntimeMesh->bUseComplexAsSimpleCollision = false;
}

// Called when the game starts or when spawned
void AAnimatedTerrain::BeginPlay()
{
	Super::BeginPlay();
	
	//RuntimeMesh->SetMeshSectionVisible(0, false);
//	initTexture();
//	initMaterial();
//	initColor();
}

//void AAnimatedTerrain::initTexture()
//{
//	reliefMapTexture = UTexture2D::CreateTransient(mapLength, mapWidth, PF_B8G8R8A8);
//	auto dataPtr = static_cast<uint8*>(reliefMapTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
//
//	//设置像素值
//	int cnt = 0;
//	for (int i = 0; i < mapLength; i++)
//	{
//		for (int j = 0; j < mapWidth; j++)
//		{
//			//	*dataPtr++ = colorValue[cnt].B;
//			//	*dataPtr++ = colorValue[cnt].G;
//			//	*dataPtr++ = colorValue[cnt].R;
//			/**dataPtr++ = fitValue[i*mapWidth + j];
//			*dataPtr++ = fitValue[i*mapWidth + j];
//			*dataPtr++ = fitValue[i*mapWidth + j];*/
//			*dataPtr++ = 255;
//			*dataPtr++ = 0;
//			*dataPtr++ = 0;
//			*dataPtr++ = 255;
//			cnt++;
//		}
//	}
//	//解锁、更新纹理
//	reliefMapTexture->PlatformData->Mips[0].BulkData.Unlock();
//	reliefMapTexture->UpdateResource();
//}
//
//void AAnimatedTerrain::initMaterial()
//{
//	//reliefMapTexture = UTexture2D::CreateTransient(HalfLength*2, HalfWidth*2, PF_B8G8R8A8);
//	DynamicMaterial = UMaterialInstanceDynamic::Create(terrainMaterial, this);
////	DynamicMaterial->SetTextureParameterValue(FName("flexBaconTex"), reliefMapTexture1);
//}
//
//void AAnimatedTerrain::updateMeterial()
//{
//	updateTextureMethod();
//
//	//textureMaker.update();
//	//reliefMapTexture = textureMaker.getTexture();
//
////	DynamicMaterial->SetTextureParameterValue(FName("flexBaconTex"), reliefMapTexture1);
//		
//	RuntimeMesh->SetMaterial(0, DynamicMaterial);
//}

void AAnimatedTerrain::Generate()
{
	TArray<FVector> Positions;
	TArray<FRuntimeMeshVertexNoPosition> VertexData;
	TArray<int32> Triangles;


	// Oversized bounding box so we don't have to update it
	BoundingBox = FBox(FVector(-HalfWidth * CellSize, -HalfWidth * CellSize, -100), FVector(HalfWidth * CellSize, HalfWidth * CellSize, 100));

	float Scale = CellSize / 50.0f;
	// Create the vertex array
	for (int32 YIndex = -HalfWidth; YIndex < HalfWidth; YIndex++)
	{
		for (int32 XIndex = -HalfWidth; XIndex < HalfWidth; XIndex++)
		{
			//设置此点在xoy平面的位置 x,y*偏移，0
			Positions.Add(FVector(XIndex * CellSize, YIndex * CellSize, 0));
			// 1UC channel，用于离散位置信息
			VertexData.Add(FRuntimeMeshVertexNoPosition(FVector(0, 0, 1), FRuntimeMeshTangent(-1, 0, 0), FVector2D(XIndex * Scale, YIndex * Scale)));
		}
	}

	// Create the triangle array
	URuntimeMeshLibrary::CreateGridMeshTriangles(HalfWidth * 2, HalfWidth * 2, true, Triangles);

	//使用双缓冲区。每帧更新
	// Here we're going to use a dual buffer section for performance since we'll be updating positions only each frame
	RuntimeMesh->CreateMeshSectionDualBuffer(0, Positions, VertexData, Triangles, BoundingBox, false, EUpdateFrequency::Frequent);

	// 还未generate
	bGenerated = true;
}


// Called every frame
void AAnimatedTerrain::Tick(float DeltaTime)
{
//	Super::Tick(DeltaTime);
//
//	if (!bGenerated)
//	{
//		Generate();
//	}
////	RuntimeMesh->ClearCollisionConvexMeshes();
//
////	getDepthValue();
//	setTestDepthValue();
//
////	RuntimeMesh->SetMeshSectionVisible(0, false);
//
//	// Start position only update
//	TArray<FVector>& Positions = *RuntimeMesh->BeginMeshSectionPositionUpdate(0);
//
//	ParallelFor((HalfWidth * 2)*(HalfLength * 2), [this, &Positions](int32 Index)
//	{
//		//int32 PlaneWidth = HalfWidth * 2;
//		//// 二维 X坐标，（列
//		//int32 XIndex = Index % PlaneWidth;
//		//// 二维 Y坐标，(行
//		//int32 YIndex = Index / PlaneWidth;
//
//		//float Scale = CellSize / 50.0f;
//		////float Scale = 1.0f;
//		//float HeightScale = FMath::Cos((XIndex * Scale) + AnimationOffsetX) + FMath::Sin((YIndex * Scale) + AnimationOffsetY);
//
//		//Positions[Index].Z = HeightScale * Height;
//
//		float Scale = CellSize / scalingFactor;
//		Positions[Index].Z = depthValue[Index]*Scale;
//	//	Positions[Index].Z = Index%200;
//	});
//	if (flagC<10)
//	{
//		flagC ++;
////		if(flagC==9)
//		//RuntimeMesh->AddCollisionConvexMesh(Positions);
//	}
//	
////	updateMeterial();
//
//	// Commit position only update (sends updates to GPU)
//	RuntimeMesh->EndMeshSectionPositionUpdate(0, BoundingBox);

	Super::Tick(DeltaTime);

	//generate
	if (!bGenerated)
	{
		Generate();
	}

	cnt++;

	if (1)
	{

		float AnimationStepX = 5;
		float AnimationStepY = 6;

		AnimationOffsetX += DeltaTime * AnimationStepX;
		AnimationOffsetY += DeltaTime * AnimationStepY;

		// Start position only update
		TArray<FVector>& Positions = *RuntimeMesh->BeginMeshSectionPositionUpdate(0);

		//离散点的个数，
		ParallelFor((HalfWidth * 2)*(HalfWidth * 2), [this, &Positions](int32 Index)
		{
			// 宽
			int32 PlaneWidth = HalfWidth * 2;	
			// 
			int32 XIndex = Index % PlaneWidth;
			int32 YIndex = Index / PlaneWidth;

			float Scale = CellSize / 50.0f;

			// 设置高度
			float HeightScale = FMath::Cos((XIndex * Scale) + AnimationOffsetX) + FMath::Sin((YIndex * Scale) + AnimationOffsetY);

			Positions[Index].Z = HeightScale * Height;

		});
	//	if (cnt == 10)
	//		RuntimeMesh->AddCollisionConvexMesh(Positions);
		// Commit position only update (sends updates to GPU)
		RuntimeMesh->EndMeshSectionPositionUpdate(0, BoundingBox);
	}
}

void AAnimatedTerrain::OnConstruction(const FTransform& Transform)
{
	Generate();
}

// test
//
//int AAnimatedTerrain::calLength(int x, int y)
//{
//	return (x - 240)*(x - 240) + (y - 320)*(y - 320);
//}
//
//void AAnimatedTerrain::setTestDepthValue()
//{
//	for (int i = 0; i < HalfLength*2; i++)
//	{
//		for (int j = 0; j < HalfWidth*2; j++)
//		{
//			//depthValue[i*mapWidth + j] = rand() % 255;
//			int tmp = calLength(i, j);
//			setCircle(i, j, tmp);
//		}
//	}
//}
//
//void AAnimatedTerrain::setCircle(int i, int j, int tmp)
//{
////	int mapWidth = HalfWidth * 2;
//	//设置值为 { 0,25, 50,75, 100,125, 150,175, 200,255, 255 };
//	if (tmp < 16000)
//		depthValue[i*mapWidth + j] = 1;
//	else if (tmp < 32000)
//		depthValue[i*mapWidth + j] = 26;
//	else if (tmp < 48000)
//		depthValue[i*mapWidth + j] = 51;
//	else if (tmp < 48000)
//		depthValue[i*mapWidth + j] = 51;
//	else if (tmp < 64000)
//		depthValue[i*mapWidth + j] = 76;
//	else if (tmp < 80000)
//		depthValue[i*mapWidth + j] = 101;
//	else if (tmp < 96000)
//		depthValue[i*mapWidth + j] = 126;
//	else if (tmp < 112000)
//		depthValue[i*mapWidth + j] = 151;
//	else if (tmp < 128000)
//		depthValue[i*mapWidth + j] = 176;
//	else if (tmp < 144000)
//		depthValue[i*mapWidth + j] = 201;
//	else if (tmp < 160000)
//		depthValue[i*mapWidth + j] = 255;
//}
//
//
//// relief map
//
//void AAnimatedTerrain::initColor()
//{
//	value_interval.Init(0, 11);
//	color_interval.Init(FColor::Black, 10);
//	colorValue.Init(FColor::Blue, sumNumber);
//	//设置值为 { 0,25, 50,75, 100,125, 150,175, 200,255, 255 };
//	value_interval[0] = 0;
//	for (int i = 1; i < 10; i++)
//		value_interval[i] = value_interval[i - 1] + 25;
//	value_interval[10] = 255;
//
//	color_interval[0] = FColor(255, 0, 0);
//	color_interval[1] = FColor(255, 29, 0);
//	color_interval[2] = FColor(255, 88, 13);
//	color_interval[3] = FColor(255, 137, 13);
//	color_interval[4] = FColor(255, 205, 23);
//	color_interval[5] = FColor(227, 1, 14);
//	color_interval[6] = FColor(0, 242, 0);
//	color_interval[7] = FColor(0, 242, 200);
//	color_interval[8] = FColor(0, 122, 242);
//	color_interval[9] = FColor(0, 0, 242);
//
//}
//
//void AAnimatedTerrain::setTexture()
//{
//	//锁定纹理，获取纹理首地址
//	auto dataPtr = static_cast<uint8*>(reliefMapTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
//
//	//设置像素值
//	int cnt = 0;
//	for (int i = 0; i < mapLength; i++)
//	{
//		for (int j = 0; j < mapWidth; j++)
//		{
//		//	*dataPtr++ = colorValue[cnt].B;
//		//	*dataPtr++ = colorValue[cnt].G;
//		//	*dataPtr++ = colorValue[cnt].R;
//			/**dataPtr++ = fitValue[i*mapWidth + j];
//			*dataPtr++ = fitValue[i*mapWidth + j];
//			*dataPtr++ = fitValue[i*mapWidth + j];*/
//			*dataPtr++ = 255;
//			*dataPtr++ = 0;
//			*dataPtr++ = 0;
//			*dataPtr++ = 255;
//			cnt++;
//		}
//	}
//	//解锁、更新纹理
//	reliefMapTexture->PlatformData->Mips[0].BulkData.Unlock();
//	reliefMapTexture->UpdateResource();
//}
//
//void AAnimatedTerrain::updateTextureColor()
//{
//	for (int i = 0; i < mapLength; i++)
//	{
//		for (int j = 0; j < mapWidth; j++)
//		{
//			if (i >= 480)
//			{
//				colorValue[i*mapWidth+j]=FColor::Black;
//				continue;
//			}
//			if (depthValue[i*mapWidth + j] < value_interval[0])
//				colorValue[i*mapWidth + j] = FColor::Black;
//			else if (depthValue[i*mapWidth + j]>value_interval[value_interval.Num() - 1])
//				colorValue[i*mapWidth + j] = FColor::Black;
//			else
//			{
//				int flag = 0;
//				for (int k = 0; k < value_interval.Num() - 1; k++)
//				{
//					if (depthValue[i*mapWidth + j] >= value_interval[k] && depthValue[i*mapWidth + j] < value_interval[k + 1])
//					{
//						if (abs(depthValue[i*mapWidth + j] - value_interval[k]) < 0.1 || abs(depthValue[i*mapWidth + j] - value_interval[k + 1]) < 0.1)
//							colorValue[i*mapWidth + j] = FColor::Black;
//						else
//							colorValue[i*mapWidth + j] = color_interval[k];
//						flag = 1;
//					}
//				}
//				if (flag == 0)
//				{
//					colorValue[i*mapWidth + j] = FColor::Black;
//				}
//			}
//		}
//	}
//}
//
//bool AAnimatedTerrain::checkCoordinate(int x, int y)
//{
//	if (x < 0 || x >= mapLength || y < 0 || y >= mapWidth)
//		return false;
//	else
//		return true;
//}
//
//bool AAnimatedTerrain::checkCounter(int x, int y)
//{
//	TArray<FColor> colorArea;
//	bool checkFlag = 0;
//	if (checkCoordinate(x + 1, y))
//	{
//		colorArea.Add(colorValue[(x + 1)*mapWidth + y]);
//	}
//	if (checkCoordinate(x + 1, y + 1))
//	{
//		colorArea.Add(colorValue[(x + 1)*mapWidth + y + 1]);
//	}
//	if (checkCoordinate(x, y + 1))
//	{
//		colorArea.Add(colorValue[(x)*mapWidth + y + 1]);
//	}
//	FColor tmp = colorValue[x*mapWidth + y];
//	for (int i = 0; i < colorArea.Num(); i++)
//	{
//		if (tmp != colorArea[i])
//		{
//			checkFlag = 1;
//			break;
//		}
//	}
//	if (checkFlag)
//		return true;
//	else
//		return false;
//}
//
//void AAnimatedTerrain::drawContour()
//{
//	counterFlag.Init(0, sumNumber);
//	for (int i = 0; i < mapLength; i++)
//	{
//		for (int j = 0; j < mapWidth; j++)
//		{
//			if (checkCounter(i, j))
//				counterFlag[i*mapWidth + j] = 1;
//		}
//	}
//	for (int i = 0; i < mapLength; i++)
//	{
//		for (int j = 0; j < mapWidth; j++)
//		{
//			if (counterFlag[i*mapWidth + j])
//				colorValue[i*mapWidth + j] = FColor::Black;
//		}
//	}
//}
//
//void AAnimatedTerrain::updateTextureMethod()
//{
//	//getDepthValue();
///*
//	updateTextureColor();
//	drawContour();
//	setTexture();*/
//}