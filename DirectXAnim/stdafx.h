#pragma once

#include "../DirectXAnimDLL/stdafx.h"
#pragma comment(lib, "DirectXAnimDLL.lib")

#include <Mmsystem.h>

#include <d3d9.h>

#include <chrono>
#include <ctime>

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

// A structure for our custom vertex type
struct CUSTOMVERTEX2D
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

// A structure for our custom vertex type
struct CUSTOMVERTEX3D
{
    FLOAT x, y, z; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX3D (D3DFVF_XYZ|D3DFVF_DIFFUSE)

// A structure for our custom vertex type
struct CUSTOMVERTEX3DN
{
    D3DXVECTOR3 position; // The 3D position for the vertex
    D3DXVECTOR3 normal;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX3DN (D3DFVF_XYZ|D3DFVF_NORMAL)

#define RANDCOLOR (D3DCOLOR_XRGB(rand()%256, rand()%256, rand()%256))

#include "Sprite.h"

#include "DXTriangle.h"
#include "DXQuad.h"
#include "DXPlane.h"

#include "DXTriangle3D.h"
#include "DXCube.h"
#include "DXCuboid.h"
#include "DXTerrain.h"

#include "Game.h"