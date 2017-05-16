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
	const int32 HalfWidth = 320;
	const int32 HalfLength = 320;
	const int32 mapLength = 640;
	const int32 mapHeight = 640;
	const int32 mapWidth = 640;
	const int32 realHeight = 480;
	const int32 sumNumber = 409600;
	const int32 realSumNumber = 307200;

	TArray<int> depthValue;

	bool checkInRealMap(int x, int y) const;
	bool checkInMap(int x, int y) const;

	//void operator= (DepthFrame newDepthFrame)
	//{
	//	//*this = newDepthFrame;
	//}

};

#endif
