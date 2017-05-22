// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef DEPTHFRAME_H
#define DEPTHFRAME_H
/**
 * 
 */

class ARSANDBOX_API DepthFrame
{
public:
	DepthFrame();
	~DepthFrame();

public:
	int mapHeight = 512;
	int mapWidth = 512;
	int realHeight = 424;
	int HalfWidth = 256;
	int HalfLength = 256;
	int32 sumNumber = 512*512;
	int32 realSumNumber = 512*424;

	TArray<int> depthValue;

	bool checkInRealMap(int x, int y) const;
	bool checkInMap(int x, int y) const;

	//void operator= (DepthFrame newDepthFrame)
	//{
	//	//*this = newDepthFrame;
	//}

};

#endif
