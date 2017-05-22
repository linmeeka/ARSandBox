// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "AnimatedTerrain.h"
#include "RuntimeMeshLibrary.h"
#include "DrawDebugHelpers.h "
#include "ParallelFor.h"
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

}

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
			//????????xoy?????¦Ë?? x,y*????0
			Positions.Add(FVector(XIndex * CellSize, YIndex * CellSize, 0));
			// 1UC channel?????????¦Ë?????
			VertexData.Add(FRuntimeMeshVertexNoPosition(FVector(0, 0, 1), FRuntimeMeshTangent(-1, 0, 0), FVector2D(XIndex * Scale, YIndex * Scale)));
		}
	}

	// Create the triangle array
	URuntimeMeshLibrary::CreateGridMeshTriangles(HalfWidth * 2, HalfWidth * 2, true, Triangles);

	//??????????????????
	// Here we're going to use a dual buffer section for performance since we'll be updating positions only each frame
	RuntimeMesh->CreateMeshSectionDualBuffer(0, Positions, VertexData, Triangles, BoundingBox, false, EUpdateFrequency::Frequent);

	// ??¦Ägenerate
	bGenerated = true;
}


// Called every frame
void AAnimatedTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	cnt++;
	//generate
	if (!bGenerated)
	{
		Generate();
	}


	float AnimationStepX = 5;
	float AnimationStepY = 6;

	if (cnt < 50)
	{
		AnimationOffsetX += DeltaTime * AnimationStepX;
		AnimationOffsetY += DeltaTime * AnimationStepY;

	}


		// Start position only update
		TArray<FVector>& Positions = *RuntimeMesh->BeginMeshSectionPositionUpdate(0);

		//????????????
		ParallelFor((HalfWidth * 2)*(HalfWidth * 2), [this, &Positions](int32 Index)
		{
			// ??
			int32 PlaneWidth = HalfWidth * 2;
			// 
			int32 XIndex = Index % PlaneWidth;
			int32 YIndex = Index / PlaneWidth;

			float Scale = CellSize / 50.0f;

			// ??????
			float HeightScale = FMath::Cos((XIndex * Scale) + AnimationOffsetX) + FMath::Sin((YIndex * Scale) + AnimationOffsetY);

			Positions[Index].Z = HeightScale * Height;

		});

		for (int i = 0; i < HalfWidth * 2; i++)
		{
			for (int j = 0; j < HalfWidth * 2; j++)
			{
				int index = i*(HalfWidth * 2) + j;
				FVector nowPosition = Positions[index];
				nowPosition.Z += 1000;
				nowPosition.X -= 3000;
				DrawDebugPoint(GetWorld(), nowPosition, 2, FColor::Red);
			}
		}
	
	// Commit position only update (sends updates to GPU)
	RuntimeMesh->EndMeshSectionPositionUpdate(0, BoundingBox);
}




void AAnimatedTerrain::OnConstruction(const FTransform& Transform)
{
	Generate();
}
