// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "depthFrameGetter.h"

// Sets default values
AdepthFrameGetter::AdepthFrameGetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AdepthFrameGetter::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add(TEXT("DepthFrameGetter"));
	sumNum = 512 * 424;
}

// Called every frame
void AdepthFrameGetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	getDepthFrameFromeKinect(depthFrame);
}

void AdepthFrameGetter::getDepthFrameFromRealSense(DepthFrame * &depthFrame)
{
	frameCount++;
	TArray <UCameraStreamComponent*> components;
	GetComponents<UCameraStreamComponent>(components);
	for (int i = 0; i < components.Num(); i++)
	{
		if (components[i] != NULL)
		{
			cameraStream = components[i];
			if (cameraStream != NULL)	
			{
				if (cameraStream->DepthBuffer.Num() != 0)
				{
					sumNum = cameraStream->DepthBuffer.Num();
					for (int j = 0; j < sumNum; j++)
					{
						//depthFrame->depthValue[j]= 255-cameraStream->DepthBuffer[j];
						depthFrame->depthValue[j] = cameraStream->DepthBuffer[j];
					}
				}
			}
			break;
		}
	}
}

void AdepthFrameGetter::getDepthFrameFromeKinect(DepthFrame * &depthFrame)
{
	frameCount++;
	if (frameCount >= 500)
		return;
	TArray<AActor*> actorList;
	TSubclassOf<AKinectFrameManager> classToFind;
	classToFind = AKinectFrameManager::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorList);

	for (int i = 0; i < actorList.Num(); i++)
	{
		if (actorList[i]->Tags[0] == TEXT("kinectFrameManager"))
		{
			kinectFrameManager = Cast<AKinectFrameManager>(actorList[i]);
			break;
		}
	}

	depthFrame->realHeight = kinectFrameManager->iHeight;
	depthFrame->mapHeight = depthFrame->mapWidth = kinectFrameManager->iWidth;
	depthFrame->realSumNumber = kinectFrameManager->iHeight*kinectFrameManager->iWidth;
	depthFrame->sumNumber = kinectFrameManager->iWidth*kinectFrameManager->iWidth;

	for (int i = 0; i < depthFrame->realSumNumber; i++)
	{
		//int depth = kinectframemanager->depthvalue[i] >> 3;
		int depth = kinectFrameManager->depthValue[i];
		depthFrame->depthValue[i] = depth;
	}
}

void AdepthFrameGetter::set(const TArray<int> &newDepthValue)
{
	for (int i = 0; i < depthFrame->realSumNumber;i++)
	{
		depthFrame->depthValue[i] = newDepthValue[i];
	}
}
