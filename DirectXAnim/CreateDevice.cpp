//-----------------------------------------------------------------------------
// File: CreateDevice.cpp
//
// Desc: This is the first tutorial for using Direct3D. In this tutorial, all
//       we are doing is creating a Direct3D device and using it to clear the
//       window.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include "stdafx.h"

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	Game::getSingleton()->Init();

    return 0;
}