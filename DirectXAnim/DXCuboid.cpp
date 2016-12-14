#include "stdafx.h"

DXCuboid::DXCuboid( LPDIRECT3DDEVICE9 _Device, FLOAT _w, FLOAT _h, FLOAT _d ) : m_pd3dDevice(_Device)
{
	FLOAT dw = _w / 2.0f;
	FLOAT dh = _h / 2.0f;
	FLOAT dd = _d / 2.0f;

	/*CUSTOMVERTEX3D vertices[] =
	{
		-1.0f * dw,  1.0f * dh, -1.0f * dd, 0xffff0000,
		-1.0f * dw,  1.0f * dh,  1.0f * dd, 0xff0000ff,
		 1.0f * dw,  1.0f * dh,  1.0f * dd, 0xffffffff,
		 1.0f * dw,  1.0f * dh, -1.0f * dd, 0xffff0000,
		-1.0f * dw, -1.0f * dh, -1.0f * dd, 0xffff0000,
		-1.0f * dw, -1.0f * dh,  1.0f * dd, 0xff0000ff,
		 1.0f * dw, -1.0f * dh,  1.0f * dd, 0xffffffff,
		 1.0f * dw, -1.0f * dh, -1.0f * dd, 0xffff0000
	};

	Game::InitVB(m_pd3dDevice, vertices, 8, &m_pVB, sizeof(CUSTOMVERTEX3D), D3DFVF_CUSTOMVERTEX3D);

	WORD indexes[] =
	{
		0, 1, 3, 2,
		4, 0, 7, 3, 6, 2, 5, 1, 4, 0,
		5, 4, 6, 7
	};

	Game::InitIB(m_pd3dDevice, indexes, 18, &m_pIB, sizeof(WORD), D3DFMT_INDEX16);*/

	CUSTOMVERTEX3DN vertices[] =
	{
		// UP
		D3DXVECTOR3(-dw,  dh, -dd), D3DXVECTOR3(0.0f, 1.0f, 0.0f),	// 0
		D3DXVECTOR3(-dw,  dh,  dd), D3DXVECTOR3(0.0f, 1.0f, 0.0f),	// 1
		D3DXVECTOR3( dw,  dh,  dd), D3DXVECTOR3(0.0f, 1.0f, 0.0f),	// 2
		D3DXVECTOR3( dw,  dh, -dd), D3DXVECTOR3(0.0f, 1.0f, 0.0f),	// 3

		// DOWN
		D3DXVECTOR3(-dw, -dh, -dd), D3DXVECTOR3(0.0f, -1.0f, 0.0f), // 4
		D3DXVECTOR3(-dw, -dh,  dd), D3DXVECTOR3(0.0f, -1.0f, 0.0f),	// 5
		D3DXVECTOR3( dw, -dh,  dd), D3DXVECTOR3(0.0f, -1.0f, 0.0f),	// 6
		D3DXVECTOR3( dw, -dh, -dd), D3DXVECTOR3(0.0f, -1.0f, 0.0f),	// 7
		
		// FRONT
		D3DXVECTOR3(-dw,  dh, -dd), D3DXVECTOR3(0.0f, 0.0f, -1.0f),	// 0
		D3DXVECTOR3( dw,  dh, -dd), D3DXVECTOR3(0.0f, 0.0f, -1.0f),	// 3
		D3DXVECTOR3( dw, -dh, -dd), D3DXVECTOR3(0.0f, 0.0f, -1.0f),	// 7
		D3DXVECTOR3(-dw, -dh, -dd), D3DXVECTOR3(0.0f, 0.0f, -1.0f),	// 4

		// BACK
		D3DXVECTOR3( dw,  dh,  dd), D3DXVECTOR3(0.0f, 0.0f, 1.0f),	// 2
		D3DXVECTOR3(-dw,  dh,  dd), D3DXVECTOR3(0.0f, 0.0f, 1.0f),	// 1
		D3DXVECTOR3(-dw, -dh,  dd), D3DXVECTOR3(0.0f, 0.0f, 1.0f),	// 5
		D3DXVECTOR3( dw, -dh,  dd), D3DXVECTOR3(0.0f, 0.0f, 1.0f),	// 6

		// LEFT
		D3DXVECTOR3(-dw,  dh,  dd), D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	// 1
		D3DXVECTOR3(-dw,  dh, -dd), D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	// 0
		D3DXVECTOR3(-dw, -dh, -dd), D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	// 4
		D3DXVECTOR3(-dw, -dh,  dd), D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	// 5

		// RIGHT
		D3DXVECTOR3( dw,  dh, -dd), D3DXVECTOR3(1.0f, 0.0f, 0.0f),	// 3
		D3DXVECTOR3( dw,  dh,  dd), D3DXVECTOR3(1.0f, 0.0f, 0.0f),	// 2
		D3DXVECTOR3( dw, -dh,  dd), D3DXVECTOR3(1.0f, 0.0f, 0.0f),	// 6
		D3DXVECTOR3( dw, -dh, -dd), D3DXVECTOR3(1.0f, 0.0f, 0.0f),	// 7
	};

	Game::InitVB(m_pd3dDevice, vertices, 24, &m_pVB, sizeof(CUSTOMVERTEX3DN), D3DFVF_CUSTOMVERTEX3DN);

	WORD indexes[] = { 0, 1, 3, 1, 2, 3, 4, 7, 5, 7, 6, 5, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };

	Game::InitIB(m_pd3dDevice, indexes, 36, &m_pIB, sizeof(WORD), D3DFMT_INDEX16);
	
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	m_Position.z = 0.0f;

	m_Rotation = 0;

	m_Material = 0;

	m_Transform = 0;
}

DXCuboid::~DXCuboid()
{
	SafeRelease( m_pVB );
	SafeRelease( m_pIB );
}

void DXCuboid::Display()
{
    D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	if(!m_Transform)
	{
		if(m_Rotation)
		{
			D3DXMATRIXA16 matRot;
			D3DXMatrixRotationQuaternion(&matRot, m_Rotation);
			matWorld *= matRot;
		}

		D3DXMATRIXA16 matPos;
		D3DXMatrixTranslation(&matPos, m_Position.x, m_Position.y, m_Position.z);
		matWorld *= matPos;

		m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	}
	else
	{
		matWorld *= (*m_Transform);

		m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	}

	if(m_Material)
		m_pd3dDevice->SetMaterial(m_Material);
	else
	{
		D3DMATERIAL9 emptyMat;
		ZeroMemory( &emptyMat, sizeof(D3DMATERIAL9) );

		emptyMat.Ambient.r = emptyMat.Ambient.g = emptyMat.Ambient.b = emptyMat.Ambient.a = 1.0f;
		emptyMat.Diffuse.r = emptyMat.Diffuse.g = emptyMat.Diffuse.b = emptyMat.Diffuse.a = 1.0f;

		m_pd3dDevice->SetMaterial( &emptyMat );
	}

	// Render the vertex buffer contents
	m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX3DN ) );
	m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3DN );
	m_pd3dDevice->SetIndices( m_pIB );

	m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12 );
}

void DXCuboid::SetPosition(FLOAT _x, FLOAT _y, FLOAT _z)
{
	m_Position.x = _x;
	m_Position.y = _y;
	m_Position.z = _z;
}

void DXCuboid::SetRotation(D3DXQUATERNION _q)
{
	if(!m_Rotation)
		m_Rotation = new D3DXQUATERNION;
	
	m_Rotation->x = _q.x;
	m_Rotation->y = _q.y;
	m_Rotation->z = _q.z;
	m_Rotation->w = _q.w;
}

void DXCuboid::SetMaterial(D3DMATERIAL9 _mat)
{
	if(!m_Material)
		m_Material = new D3DMATERIAL9;

	(*m_Material) = _mat;
}

void DXCuboid::SetTransform(D3DXMATRIXA16 *_mat)
{
	m_Transform = _mat;
}