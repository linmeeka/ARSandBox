// Fill out your copyright notice in the Description page of Project Settings.
#pragma comment(linker, "/STACK:1024000000,1024000000")  
#include "ARSandBox.h"
#include "CollisionSpawner.h"


// Sets default values
ACollisionSpawner::ACollisionSpawner()
{
	offsetX = 70;
	offsetY = -70;
	mapHeight = 640;
	mapWidth = 640;
	VertexColors.Init(FColor::White, 640 * 640);
}

void ACollisionSpawner::setCollision(const DepthFrame &depthFrame)
 {
	visitFlag.Init(1, depthFrame.sumNumber);
	collisionBodyList.Empty();
	int blackPoint = 0;
	for (int i = 0; i < depthFrame.realHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			int index = i*depthFrame.mapWidth + j;
			if (VertexColors[index]==FColor::Black)
			//if(VertexColors[index].R==255&& VertexColors[index].G == 255&& VertexColors[index].B == 255)
			{
				visitFlag[index] = false;
				blackPoint++;
			}
			if (depthFrame.depthValue[index] < minHeight)
				minHeight = depthFrame.depthValue[index];
		}
	}
	CollisionBody planeCollisionBody;
	planeCollisionBody.button = FVector(-320, -320, minHeight);
	planeCollisionBody.top = FVector(320, 320, minHeight);
	planeCollisionBody.left = FVector(-320, 320, minHeight);
	planeCollisionBody.right = FVector(320, -320, minHeight);
	planeCollisionBody.center = FVector(0, 0, minHeight);

	collisionBodyList.Add(planeCollisionBody);

	if (blackPoint > 100000)
		return;

	for (int i = 0; i < depthFrame.realHeight; i++)
	{
		for (int j = 0; j <depthFrame.mapWidth; j++)
		{
			if (visitFlag[i*depthFrame.mapWidth + j] == false)
			{

				//初始化为第一个点
				newCollisionBody.button = newCollisionBody.left = newCollisionBody.right = newCollisionBody.top = FVector(i,j, depthFrame.depthValue[i*depthFrame.mapWidth + j]);
				
				//计算
				pointCount = 0;
				//int pointCount = 0;
				calculateEdge(i, j, newCollisionBody,pointCount);
				if (pointCount < pointCountTreshold)
					continue;
				else
					newCollisionBody.sumPoint = pointCount;

				newCollisionBody.center = calculateCenter(newCollisionBody); 

				//更新Z坐标
				calculateEdgeDepth(newCollisionBody.button, depthFrame.depthValue);
				calculateEdgeDepth(newCollisionBody.top, depthFrame.depthValue);
				calculateEdgeDepth(newCollisionBody.left, depthFrame.depthValue);
				calculateEdgeDepth(newCollisionBody.right, depthFrame.depthValue);

			/*	newCollisionBody.button.Z = minHeight;
				newCollisionBody.top.Z = minHeight;
				newCollisionBody.left.Z = minHeight;
				newCollisionBody.right.Z = minHeight;*/

					if (checkPlane(newCollisionBody))
					newCollisionBody.center.Z = minHeight;
				else
				{
					calculateEdgeDepth(newCollisionBody.center, depthFrame.depthValue);
				//	newCollisionBody.center.Z = 150;

				}

				//坐标系转换
				transformationCenter(newCollisionBody.button);
				transformationCenter(newCollisionBody.top);
				transformationCenter(newCollisionBody.left);
				transformationCenter(newCollisionBody.right);
				transformationCenter(newCollisionBody.center);

				//添加
				collisionBodyList.Add(newCollisionBody);
			}
		}
	}
}

bool ACollisionSpawner::checkPlane(CollisionBody newCollisionBody)
{
	if ((abs((int)newCollisionBody.left.X - 0) < 10)
		&& (abs((int)newCollisionBody.right.X - mapWidth) < 10)
		&& (abs((int)newCollisionBody.button.Y - 0) < 10)
		&& (abs((int)newCollisionBody.top.Y - mapHeight) < 10))
		return true;
	else
		return false;
}

FVector ACollisionSpawner::calculateCenter(const CollisionBody newCollisionBody)
{
	FVector center;
	center.X = (newCollisionBody.left.X + newCollisionBody.right.X) / 2;
	center.Y = (newCollisionBody.top.Y + newCollisionBody.button.Y) / 2;
	center.Z = 0;
	return center;
}

bool ACollisionSpawner::checkInMap(int x, int y)
{
	if (x < 0 || x >= realHeight || y < 0 || y >= mapWidth)
		return false;
	else
		return true;
}

bool ACollisionSpawner::checkDir(int x, int y)
{
	if ((!checkInMap(x,y)) || visitFlag[x*mapWidth + y] == true)
		return false;
	else
		return true;
}

void ACollisionSpawner::calculateEdge(int startX, int startY, CollisionBody &newCollisionBody, int &pointCount)
 {
	 pointCount++;
	visitFlag[startX*mapWidth+startY] = true;
	VertexColors[startX*mapWidth + startY] = FColor::Red;
	bool movingFlag = false;
	if (startX < newCollisionBody.left.X)
	{
		newCollisionBody.setCoordinate2(newCollisionBody.left, startX, startY);
	}
	if (startX > newCollisionBody.right.X)
	{
		newCollisionBody.setCoordinate2(newCollisionBody.right, startX, startY);
	}
	if (startY < newCollisionBody.button.Y)
	{
		newCollisionBody.setCoordinate2(newCollisionBody.button, startX, startY);
	}
	if (startY > newCollisionBody.top.Y)
	{
		newCollisionBody.setCoordinate2(newCollisionBody.top, startX, startY);
	}

	for (int i = 0; i < 4; i++)
	{
		int nextX = startX + dir[i][0];
		int nextY = startY + dir[i][1];
 		if (checkDir(nextX, nextY))
		{
			movingFlag = true;
			calculateEdge(nextX, nextY, newCollisionBody, pointCount);
		}
	}
	if (!movingFlag)
		return;
}

void ACollisionSpawner::calculateEdgeDepth(FVector &point, const TArray<int> &depthValue)
{

	resultPoint = point;
	resultPoint.Z = depthValue[((int)point.X)*mapWidth + (int)point.Y];
	for (int i = 0; i < 8; i++)
	{
		adjacentPoint.X = point.X + dir[i][0]*1.0;
		adjacentPoint.Y = point.Y + dir[i][1]*1.0;
		if (checkInMap(adjacentPoint.X, adjacentPoint.Y))
		{
			adjacentPoint.Z = depthValue[((int)(adjacentPoint.X))*mapWidth + (int)adjacentPoint.Y];
			if (adjacentPoint.Z < resultPoint.Z)
				resultPoint = adjacentPoint;
		}
	}
	point.Z = resultPoint.Z;
}

void ACollisionSpawner::setEdgeColor(const TArray<FColor> &terrainColor)
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (terrainColor[i*mapWidth + j] != FColor::Black)
				VertexColors[i*mapWidth + j] = FColor::White;
			else
				VertexColors[i*mapWidth + j] = terrainColor[i*mapWidth + j];
		}
	}
}