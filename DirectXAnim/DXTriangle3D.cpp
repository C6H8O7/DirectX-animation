#include "stdafx.h"

DXTriangle3D::DXTriangle3D( LPDIRECT3DDEVICE9 _Device, CUSTOMVERTEX3D *_customvertices ) : m_pd3dDevice(_Device)
{
	Game::InitVB(m_pd3dDevice, _customvertices, 3, &m_pVB, sizeof(CUSTOMVERTEX3D), D3DFVF_CUSTOMVERTEX3D);
}

DXTriangle3D::~DXTriangle3D()
{
	SafeRelease( m_pVB );
}

void DXTriangle3D::Display()
{
	// For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 matWorld;

    // Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
    // every 1000 ms. To avoid the loss of precision inherent in very high 
    // floating point numbers, the system time is modulated by the rotation 
    // period before conversion to a radian angle.
    UINT iTime = timeGetTime() % 1000;
    FLOAT fAngle = iTime * ( 2.0f * D3DX_PI ) / 1000.0f;
    D3DXMatrixRotationY( &matWorld, fAngle );
    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	// Render the vertex buffer contents
	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX3D ) );
	m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 1 );
}