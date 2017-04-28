// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "FuildSpawner.h"


// Sets default values
AFuildSpawner::AFuildSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	loadParticle();
}

// Called when the game starts or when spawned
void AFuildSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuildSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuildSpawner::loadParticle()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> MyParticleSystem(TEXT("ParticleSystem'/Game/TestPackages/Flex/flexTestEmitterSurfaceSlower.flexTestEmitterSurfaceSlower'"));
//	static ConstructorHelpers::FObjectFinder<UParticleSystem> MyParticleSystem(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (MyParticleSystem.Succeeded())
	{
		TestParticle = MyParticleSystem.Object;
	}
}

void AFuildSpawner::initFuild()
{
	UWorld *world = GetWorld();
	FTransform initTransform;
	initTransform.SetLocation(FVector(1000, 0, 0));
	LastPSC = UGameplayStatics::SpawnEmitterAtLocation(world, TestParticle, initTransform);
	initFlag = true;
}

void AFuildSpawner::spawnFuild(FTransform spawnTransform)
{
	LastPSC->SetWorldTransform(spawnTransform);
}

void AFuildSpawner::destoryFuild()
{
//	LastPSC->ActivateSystem(false);
//	LastPSC->DestroyComponent();
//	LastPSC->DestroyComponent(true);
	FTransform tmp;
	tmp.SetLocation(FVector(500, 0, 500));
	tmp.SetRotation(FQuat(90, 0, 0, 1));
	LastPSC->SetWorldTransform(tmp);
	
}

void AFuildSpawner::calPlaneDepth(const DepthFrame &depthFrame)
{
	if (!initFlag)
		initFuild();

	depthPointCount.Empty();
	intervalPointCount.Empty();
	for (int i = 0; i < depthFrame.realHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			int index = i*depthFrame.mapWidth + j;
			if (depthPointCount.Contains(depthFrame.depthValue[index]))
			{
				int &valuePtr = depthPointCount.FindOrAdd(depthFrame.depthValue[index]);
				valuePtr++;
			}
			else
				depthPointCount.Add(depthFrame.depthValue[index], 1);
		}
	}
	depthPointCount.KeySort([](int32 A, int32 B) {
		return A > B; // sort keys in reverse
	});
	for (TMap<int, int>::TConstIterator iter=depthPointCount.CreateConstIterator(); iter; ++iter)
	{
		int tmpSum = 0;
		int nowDepth = iter.Key();
		int maxPlane = iter.Key() + planeThreshold;
		int minPlane = iter.Key() - planeThreshold;
		if (minPlane<0)
			minPlane = 0;
		for (TMap<int, int>::TConstIterator iter1 = depthPointCount.CreateConstIterator(); iter1; ++iter1)
		{
			if (iter1.Key() > maxPlane)
			{
				break;
			}
			else if (iter1.Key() >= minPlane&&iter1.Key() <= maxPlane)
			{
				tmpSum += iter1.Value();
			}
		}
		intervalPointCount.Add(iter.Key(), tmpSum);
	}
	planeDepth = 0;
	planeCount = -1;
	for (TMap<int, int>::TConstIterator iter = intervalPointCount.CreateConstIterator(); iter; ++iter)
	{
		if (iter.Value() > planeCount)
		{
			planeCount = iter.Value();
			planeDepth = iter.Key();
		}
	}
}
