#include "stdafx.h"

DXQuad::DXQuad(LPDIRECT3DDEVICE9 _device, CUSTOMVERTEX2D *_customvertices) : m_pd3dDevice(_device)
{
	Game::InitVB(m_pd3dDevice, _customvertices, 4, &m_pVB, sizeof(CUSTOMVERTEX2D), D3DFVF_CUSTOMVERTEX2D);
}

DXQuad::DXQuad(LPDIRECT3DDEVICE9 _device, FLOAT _x, FLOAT _y, FLOAT _w, FLOAT _h, DWORD _color) : m_pd3dDevice(_device)
{
	CUSTOMVERTEX2D vertices[] =
	{
		{ _x, _y, 0.5f, 1.0f, _color },
		{ _x + _w, _y, 0.5f, 1.0f, _color },
		{ _x, _y + _h, 0.5f, 1.0f, _color },
		{ _x + _w, _y + _h, 0.5f, 1.0f, _color }
	};

	Game::InitVB(m_pd3dDevice, vertices, 4, &m_pVB, sizeof(CUSTOMVERTEX2D), D3DFVF_CUSTOMVERTEX2D);
}

DXQuad::~DXQuad()
{
	SafeRelease( m_pVB );
}

void DXQuad::Display()
{
	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX2D ) );
    m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX2D );
	m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
}