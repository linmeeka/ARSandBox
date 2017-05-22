// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <queue>
#include "DepthFrame.h"

using namespace std;

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
	//const int mapHeight = 640;
	//const int mapWidth = 640;
	//const int realHeight = 480;
	const int mapHeight = 512;
	const int mapWidth = 512;
	const int realHeight = 424;
	int offsetX, offsetY;
	int dir[8][2] = { 1,0,-1,0,0,1,0,-1,1,1,1,-1,-1,1,-1,-1 };
	const int pointCountTreshold = 100;

	TArray<bool> visitFlag;
	TArray<FColor> VertexColors;
	void calculateEdge(int startX, int startY, CollisionBody &newCollisionBody,int &pointCount);
	void calculateEdge_BFS(FVector2D curPosition, CollisionBody &newCollisionBody, int &pointCount);
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
