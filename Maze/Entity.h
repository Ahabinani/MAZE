#pragma once
#include <chrono>
class Entity
{
public:
	int iCoordX;
	int iCoordY;
	int iMoveCount;
	std::chrono::duration<double> tTime;
};

