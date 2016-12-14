#include "stdafx.h"

Game::Game()
{

}

Game::~Game()
{

}

Game *Game::getSingleton()
{
	static Game instanceUnique;

	return &instanceUnique;
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT Game::InitD3D( HWND hWnd )
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

	D3DDISPLAYMODE mode;
	m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &mode );

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow			 = m_hWnd;
	d3dpp.BackBufferWidth        = WINDOW_WIDTH;
    d3dpp.BackBufferHeight       = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	InitViewAndPerspective();

	InitLight();

    // Device state would normally be set here

	D3DXCreateTextureFromFile(m_pd3dDevice, L"missile.png", &m_pTexture);

	m_pSprite = new Sprite(m_pd3dDevice);
	m_pSprite->SetTexture(m_pTexture);
	
	m_pTerrain = new DXTerrain(m_pd3dDevice, 5, 3, 0.5f, 10, 10);

	AnimationManager::getSingleton()->loadAnimFromFile("anim", "Biped.skeleton.xml");
	AnimationManager::getSingleton()->getAnimation("anim")->setDevice(m_pd3dDevice);
	AnimationManager::getSingleton()->getAnimation("anim")->loadMeshFromFile("Biped.mesh.xml");

	m_Anim = new AnimationInstance(AnimationManager::getSingleton()->getAnimation("anim"), "anim_name", "Walk");
	m_Anim->getControllerPtr()->setSpeed(1.0f);

	m_Mesh = new Mesh(*AnimationManager::getSingleton()->getAnimation("anim")->getMeshPtr());

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: InitViewAndPerspective()
// Desc: Sets up the view and projection transform Matrices.
//-----------------------------------------------------------------------------
VOID Game::InitViewAndPerspective()
{
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt( 0.0f, 144.0f, 450.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 144.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 1000.0f );
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

VOID Game::InitLight()
{
	// Set up a white, directional light, with an oscillating direction.
    // Note that many lights may be active at a time (but each one slows down
    // the rendering of our scene). However, here we are just using one. Also,
    // we need to set the D3DRS_LIGHTING renderstate to enable lighting
    D3DXVECTOR3 vecDir;
    D3DLIGHT9 light;
    ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r = 1.0f;
    light.Diffuse.g = 1.0f;
    light.Diffuse.b = 1.0f;
    vecDir = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
    light.Range = 1000.0f;
	m_pd3dDevice->SetLight( 0, &light );
    m_pd3dDevice->LightEnable( 0, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    // Finally, turn on some ambient light.
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );
}

//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our Vertices. The vertex
//       buffer is basically just a chuck of memory that holds Vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT Game::InitVB(LPDIRECT3DDEVICE9 _device, void *_vertices, INT _nbVertices, LPDIRECT3DVERTEXBUFFER9 *_ppVB, UINT _sizeOfVertex, DWORD _fvf)
{
    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom Vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
    if( FAILED( _device->CreateVertexBuffer( _nbVertices * _sizeOfVertex, 0, _fvf, D3DPOOL_DEFAULT, _ppVB, NULL ) ) )
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the Vertices. This mechanism is required because vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if( FAILED( (*_ppVB)->Lock( 0, _nbVertices * _sizeOfVertex, ( void** )&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, _vertices, _nbVertices * _sizeOfVertex );
    (*_ppVB)->Unlock();

    return S_OK;
}

HRESULT Game::InitIB(LPDIRECT3DDEVICE9 _device, void *_indexes, INT _nbIndexes, LPDIRECT3DINDEXBUFFER9 *_ppIB, UINT _sizeOfIndex, D3DFORMAT _indexFormat)
{
	if( FAILED( _device->CreateIndexBuffer( _nbIndexes * _sizeOfIndex, 0, _indexFormat, D3DPOOL_DEFAULT, _ppIB, NULL ) ) )
    {
        return E_FAIL;
    }

    // Now we fill the index buffer. To do this, we need to Lock() the VB to
    // gain access to the Indexes. This mechanism is required because indexes
    // buffers may be in device memory.
    VOID* pIndexes;
    if( FAILED( (*_ppIB)->Lock( 0, _nbIndexes * _sizeOfIndex, ( void** )&pIndexes, 0 ) ) )
        return E_FAIL;
    memcpy( pIndexes, _indexes, _nbIndexes * _sizeOfIndex );
    (*_ppIB)->Unlock();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Game::Render()
{
    if( NULL == m_pd3dDevice )
        return;

    // Clear the backbuffer to a blue color
    m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 150, 235), 1.0f, 0 );
    
    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
		static Clock clock;
		LARGE_INTEGER us = clock.restart(Clock::US);
		printf("fps : %10f\r", clock.getFPS());
		float dT = us.QuadPart / (float)Clock::US;

		m_Anim->update(dT);

		Array* boneArray = m_Anim->getPosePtr()->getBoneArray();
		Bone** bones = (Bone**)boneArray->data;

		DXCuboid cuboid(m_pd3dDevice, 5, 5, 5);

		for(int i=0; i<boneArray->size; i++)
		{
			Bone *b = bones[i];

			D3DXMATRIXA16 mat = b->getWorldMatrix();

			cuboid.SetTransform(&b->getWorldMatrix());
			cuboid.Display();
		}

		m_Mesh->stickToPose(m_Anim->getPosePtr());
		m_Mesh->display();
    
        // End the scene
        m_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Game::Cleanup()
{
	SafeRelease( m_pd3dDevice );
	SafeRelease( m_pD3D );
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI Game::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					Game::getSingleton()->Cleanup();
					PostQuitMessage(0);
					break;

				default:
					Game::getSingleton()->Input();
					break;
			}
		}
        break;

        case WM_DESTROY:
            Game::getSingleton()->Cleanup();
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: Init()
// Desc: Init all
//-----------------------------------------------------------------------------
VOID Game::Init()
{
	// Get some debug stuff
	AllocConsole();
	freopen("CON", "w", stdout);

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
					  GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
					  L"D3D Tutorial", NULL };

	m_WindowsClassEx = wc;

    RegisterClassEx( &m_WindowsClassEx );
	
	RECT desktop;
	HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
   
	UINT x = desktop.right / 2 - WINDOW_WIDTH / 2;
	UINT y = desktop.bottom / 2 - WINDOW_HEIGHT / 2;

    // Create the application's window
    m_hWnd = CreateWindow( L"D3D Tutorial", L"D3D", 
                           WS_OVERLAPPEDWINDOW, x, y, WINDOW_WIDTH, WINDOW_HEIGHT,
                           hDesktop, NULL, m_WindowsClassEx.hInstance, NULL );

	// Initialize Direct3D
    if( SUCCEEDED( InitD3D( m_hWnd ) ) )
    {
		// Show the window
		ShowWindow( m_hWnd, SW_SHOWDEFAULT );
		UpdateWindow( m_hWnd );

		// Enter the message loop
		MSG msg;
		ZeroMemory( &msg, sizeof( msg ) );
		while( msg.message != WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
				Render();
		}
    }

	UnregisterClass( L"D3D Tutorial", m_WindowsClassEx.hInstance );
}

VOID Game::Input()
{
	// Display mode
	if( GetAsyncKeyState( VK_F1 ) )
	{
		DWORD mode;
		m_pd3dDevice->GetRenderState(D3DRS_FILLMODE, &mode);

		if(mode != D3DFILL_WIREFRAME)
			m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	if( GetAsyncKeyState( VK_F2 ) )
	{
		DWORD mode;
		m_pd3dDevice->GetRenderState(D3DRS_CULLMODE, &mode);

		if(mode != D3DCULL_NONE)
			m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		else
			m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	if( GetAsyncKeyState( VK_F3 ) )
	{
		DWORD mode;
		m_pd3dDevice->GetRenderState(D3DRS_LIGHTING, &mode);

		if(mode != FALSE)
			m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		else
			m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}