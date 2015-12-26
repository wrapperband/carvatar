// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#ifndef _PRECOMP_H
#define _PRECOMP_H

#define _CRT_SECURE_NO_DEPRECATE
// Activate memory leak detection in debug
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>

#include <GL/glew.h>
#include <SDL.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <iostream>
#include <assert.h>
#include <set>
#include <apiset.h>
#include <glm/glm.hpp>
#include <fstream>

#define timegm _mkgmtime
#define LOG_MAX_SIZE 1024

#define SCREEN_SIZE_WIDTH (1980)
#define SCREEN_SIZE_HEIGHT (1080)

enum INPUT_SENSOR_TYPE
{
	IS_VELOCITY,
	IS_LEFTDISTANCE,
	IS_TRACKANGLE,
	IS_RAYCAST90,
	IS_RAYCAST45,
	IS_RAYCAST0,
	IS_RAYCASTM45,
	IS_RAYCASTM90,
	IS_CARDISTANCETOCENTERLINE,

	IS_NUM
};

//key pressed
enum OUTPUT_ACTION_TYPE
{
	OA_UP,
	OA_DOWN,
	OA_LEFT,
	OA_RIGHT,

	OA_NUM
};


struct RenderData
{
	SDL_Window*	window;
	SDL_Renderer*	render;
};

struct PhysicsData
{
	b2World * world;
};

enum COLLISION_FILTERS
{
	CATEGORY_CAR = 0x0001,
	CATEGORY_STATIC = 0x0002
};

void prinfvector(float *v, unsigned int size);
void fprinfvector(FILE*f, float *v, unsigned int size);

void RotateVector(b2Vec2 vec, float angle, b2Vec2 &output);
inline void Log(const char* fmt, ...)
{
	char buf[LOG_MAX_SIZE];
	va_list ap;
	va_start(ap, fmt);
	_vsnprintf(buf, sizeof(buf) - 1, fmt, ap);
	va_end(ap);
	buf[LOG_MAX_SIZE - 1] = 0;
	printf(buf);
}

#ifdef USE_LOGGER
#define LOG(X, ...) Log(X,  __VA_ARGS__)
#else
#define LOG(fmt, ...) 
#endif
#endif
