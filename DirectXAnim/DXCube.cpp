#include "stdafx.h"

DXCube::DXCube( LPDIRECT3DDEVICE9 _Device, CUSTOMVERTEX3D *_customvertices ) : m_pd3dDevice(_Device)
{
	CUSTOMVERTEX3D vertices[] =
	{
		-1.0f, 1.0f, -1.0f, 0xffff0000,
		-1.0f, 1.0f, 1.0f, 0xff0000ff,
		1.0f, 1.0f, 1.0f, 0xffffffff,
		1.0f, 1.0f, -1.0f, 0xffff0000,
		-1.0f, -1.0f, -1.0f, 0xffff0000,
		-1.0f, -1.0f, 1.0f, 0xff0000ff,
		1.0f, -1.0f, 1.0f, 0xffffffff,
		1.0f, -1.0f, -1.0f, 0xffff0000
	};

	Game::InitVB(m_pd3dDevice, vertices, 8, &m_pVB, sizeof(CUSTOMVERTEX3D), D3DFVF_CUSTOMVERTEX3D);

	WORD indexes[] =
	{
		0, 1, 3, 2,
		4, 0, 7, 3, 6, 2, 5, 1, 4, 0,
		4, 5, 7, 6
	};

	Game::InitIB(m_pd3dDevice, indexes, 18, &m_pIB, sizeof(WORD), D3DFMT_INDEX16);
}

DXCube::~DXCube()
{
	SafeRelease( m_pVB );
	SafeRelease( m_pIB );
}

void DXCube::Display()
{
	// For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 matWorld;

    FLOAT fAngle = timeGetTime() / 10.0f * ( 2.0f * D3DX_PI ) / 1000.0f;
    D3DXMatrixRotationY( &matWorld, fAngle );
    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	// Render the vertex buffer contents
	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX3D ) );
	m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	m_pd3dDevice->SetIndices( m_pIB );
	
	m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, 8, 0, 2 );
	m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, 8, 4, 8 );
	m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, 8, 14, 2 );
}