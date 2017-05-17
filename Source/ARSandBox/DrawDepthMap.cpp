// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "DrawDepthMap.h"

void ADrawDepthMap::getDepthMap(const DepthFrame &newDepthFrame)
{
	if (initFlag == false)
	{
		depthFrame.Init(0, 480 * 640);
		initFlag = true;
	}
	for (int i = 0; i < newDepthFrame.realHeight; i++)
	{
		for (int j = 0; j < newDepthFrame.mapWidth; j++)
		{
			int index = i*newDepthFrame.mapWidth + j;
			depthFrame[index]=newDepthFrame.depthValue[index];
		}
	}
	
}

void ADrawDepthMap::DrawHUD()
{
	//先调用父类函数
	Super::DrawHUD();
	//创建纹理，分辨率，色彩类型
	depthMap = UTexture2D::CreateTransient(mapWidth, realHeight, PF_B8G8R8A8);
	setTexture();
	//绘制到屏幕
	DrawTextureSimple(depthMap, 100, 50);
}

void ADrawDepthMap::setTexture()
{
	//锁定纹理，获取纹理首地址
	auto dataPtr = static_cast<uint8*>(depthMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	//设置像素值
	int cnt = 0;
	for (int i = 0; i < realHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			int index = i*mapWidth + j;
			*dataPtr++ = depthFrame[index];
			*dataPtr++ = depthFrame[index];
			*dataPtr++ = depthFrame[index];
			/**dataPtr++ = fitValue[i*mapWidth + j];
			*dataPtr++ = fitValue[i*mapWidth + j];
			*dataPtr++ = fitValue[i*mapWidth + j];*/
			//*dataPtr++ = 255;
			//*dataPtr++ = 0;
			//*dataPtr++ = 0;
			*dataPtr++ = 255;
			cnt++;
		}
	}
	//解锁、更新纹理
	depthMap->PlatformData->Mips[0].BulkData.Unlock();
	depthMap->UpdateResource();
}

void ADrawDepthMap::BeginPlay()
{
 	Super::BeginPlay();
	this->Tags.Add(TEXT("DrawDepthMap"));
} 