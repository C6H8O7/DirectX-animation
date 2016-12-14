#include "stdafx.h"

DXTriangle::DXTriangle(LPDIRECT3DDEVICE9 _Device, CUSTOMVERTEX2D *_customvertices) : m_pd3dDevice(_Device)
{
	Game::InitVB(m_pd3dDevice, _customvertices, 3, &m_pVB, sizeof(CUSTOMVERTEX2D), D3DFVF_CUSTOMVERTEX2D);
}

DXTriangle::~DXTriangle()
{
	SafeRelease( m_pVB );
}

void DXTriangle::Display()
{
	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX2D ) );
    m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX2D );
    m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );
}