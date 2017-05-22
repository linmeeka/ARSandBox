// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "KinectFrameManager.h"


// Sets default values
AKinectFrameManager::AKinectFrameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKinectFrameManager::BeginPlay()
{
	Super::BeginPlay();
	GetDefaultKinectSensor(&pSensor);
	// 1b. Open sensor
	pSensor->Open();
	// 2a. Get frame source

	pSensor->get_DepthFrameSource(&pFrameSource);

	pFrameSource->get_FrameDescription(&pFrameDescription);
	pFrameDescription->get_Width(&iWidth);
	pFrameDescription->get_Height(&iHeight);
	pFrameDescription->Release();
	pFrameDescription = nullptr;
	// 2c. get some dpeth only meta
	UINT16 uDepthMin = 0, uDepthMax = 0;
	pFrameSource->get_DepthMinReliableDistance(&uDepthMin);
	pFrameSource->get_DepthMaxReliableDistance(&uDepthMax);

	// 3a. get frame reader
	pFrameSource->OpenReader(&pFrameReader);

	this->Tags.Add(TEXT("kinectFrameManager"));
}

// Called every frame
void AKinectFrameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IDepthFrame* pFrame = nullptr;
//	pFrame->get_DepthMaxReliableDistance(&nDepthMaxDistance);
	if (pFrameReader->AcquireLatestFrame(&pFrame) == S_OK)
	{
		// 4c. copy the depth map to image
		//	pFrame->CopyFrameDataToArray(iWidth * iHeight,reinterpret_cast<UINT16*>(depthValue));
		auto mapSize = iWidth*iHeight;
		
		//	short[] depthPixelDate = new short[mapSize];
		pFrame->CopyFrameDataToArray(mapSize, depthValue);
	//	int depth = depthValue[250 * 250] >> 3;
	//	int depth = depthValue[250 * 250];
	// 4e. release frame
		pFrame->Release();
	}

}

void AKinectFrameManager::BeginDestroy()
{
	Super::BeginDestroy();
	//// 3b. release frame reader
	//pFrameReader->Release();
	//pFrameReader = nullptr;
	//// 2d. release Frame source
	//pFrameSource->Release();
	//pFrameSource = nullptr;
	//// 1c. Close Sensor
	//pSensor->Close();
	//// 1d. Release Sensor
	//pSensor->Release();
	//pSensor = nullptr;
}