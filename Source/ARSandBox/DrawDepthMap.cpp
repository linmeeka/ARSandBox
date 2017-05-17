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
	//�ȵ��ø��ຯ��
	Super::DrawHUD();
	//���������ֱ��ʣ�ɫ������
	depthMap = UTexture2D::CreateTransient(mapWidth, realHeight, PF_B8G8R8A8);
	setTexture();
	//���Ƶ���Ļ
	DrawTextureSimple(depthMap, 100, 50);
}

void ADrawDepthMap::setTexture()
{
	//����������ȡ�����׵�ַ
	auto dataPtr = static_cast<uint8*>(depthMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	//��������ֵ
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
	//��������������
	depthMap->PlatformData->Mips[0].BulkData.Unlock();
	depthMap->UpdateResource();
}

void ADrawDepthMap::BeginPlay()
{
 	Super::BeginPlay();
	this->Tags.Add(TEXT("DrawDepthMap"));
} 