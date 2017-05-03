// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "DepthFrame.h"

DepthFrame::DepthFrame()
{
	depthValue.Init(0, 640*640);
}

DepthFrame::~DepthFrame()
{
}

bool DepthFrame::checkInRealMap(int x, int y) const
{
	if (x < 0 || x >= realHeight || y < 0 || y >= mapWidth)
		return false;
	else
		return true;
}

bool DepthFrame::checkInMap(int x, int y) const
{
	if (x < 0 || x >= mapHeight || y < 0 || y >= mapWidth)
		return false;
	else
		return true;
}