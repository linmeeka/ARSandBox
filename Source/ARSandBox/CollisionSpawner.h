// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"

struct CollisionBody
{
	FVector top, button, left, right, center;
	int sumPoint = 0;
	void setCoordinate2(FVector &edgePoint,int x,int y)
	{
		edgePoint.X = x;
		edgePoint.Y = y;
	}
};

class ACollisionSpawner
{
public:	
	// Sets default values for this actor's properties
	ACollisionSpawner();
	 
public:	
	
	TArray<CollisionBody> &getCollisionBodyList()
	{
		return collisionBodyList;
	}
	void setCollision(const DepthFrame &depthFrame);
	void setEdgeColor(const TArray<FColor> &terrainColor);
	int tmp;

private:
	TArray<CollisionBody> collisionBodyList;
	int mapHeight, mapWidth;
	int realHeight = 480;
	int minHeight=256;
	int offsetX, offsetY;
	int dir[8][2] = { 1,0,-1,0,0,1,0,-1,1,1,1,-1,-1,1,-1,-1 };
	const int pointCountTreshold = 100;

	TArray<bool> visitFlag;
	TArray<FColor> VertexColors;
	void calculateEdge(int startX, int startY, CollisionBody &newCollisionBody,int &pointCount);
	FVector calculateCenter(const CollisionBody newCollisionBody);
	bool checkInMap(int x, int y);
	bool checkDir(int x, int y);
	void calculateEdgeDepth(FVector &point, const TArray<int> &depthValue);
	void transformationCenter(FVector &point)
	{
		point.X -= mapHeight / 2;
		point.X += offsetX;
		point.Y -= mapWidth / 2;
		point.Y += offsetY;
	}
	bool checkPlane(CollisionBody newCollisionBody);


	FVector adjacentPoint, resultPoint;
	int testDepth;
	CollisionBody newCollisionBody;
	int pointCount;
};
