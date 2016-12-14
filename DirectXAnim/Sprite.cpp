/**
 * Code source Sprite
 * 
 * @author  Fabsther
 * @since   03/05/2010
 * @version 1.0
 */

#include "stdafx.h"

Sprite::Sprite( LPDIRECT3DDEVICE9 _Device )
{
	//init translation
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;

	//init rectangle
	m_pRect = NULL;

	//init center
	m_pCenter = NULL;

	//init de la rotation
	m_fRotation = 0.0f;

	//init du centre de scale
	m_pScaleCenter = NULL;

	//init de la rotation du scale
	m_fScaleRotation = 0.0f;

	//init du scale
	m_pScale = NULL;

	//init color
	m_Color = D3DCOLOR_XRGB(255, 255, 255);

	//init pointeur texture
	m_pTexture = NULL;

	m_pD3DDevice = _Device;

	//creation du sprite
	if (FAILED(D3DXCreateSprite(_Device, &m_pSprite)))
	{
		OutputDebugString(L"Failed to create Sprite.\n");
	}
}

Sprite::~Sprite()
{
	SafeDelete( m_pRect );
	SafeDelete( m_pCenter );
	SafeDelete( m_pScaleCenter );
	SafeDelete( m_pScale );

	SafeRelease( m_pTexture );
	SafeRelease( m_pSprite );
}

void Sprite::Display()
{
	// Start render loop with alpha enabled
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat, m_pScaleCenter, m_fScaleRotation, m_pScale, m_pCenter, m_fRotation, &m_Position);

	// Tell where the sprite will be rendered with a matrix
	m_pSprite->SetTransform(&mat);

	// Draw the sprite 
	m_pSprite->Draw( m_pTexture, m_pRect, NULL, NULL, m_Color );

	// Thats it
	m_pSprite->End();
}

void Sprite::SetPosition(float _x, float _y)
{
	m_Position.x = _x;
	m_Position.y = _y;
}

void Sprite::SetTexture(LPDIRECT3DTEXTURE9 _pTexture)
{
	m_pTexture = _pTexture;
}

void Sprite::SetRectangle(LONG _x, LONG _y, LONG _w, LONG _h)
{
	if(!m_pRect)
		m_pRect = new RECT;

	m_pRect->left		= _x;
	m_pRect->top		= _y;
	m_pRect->right		= _x + _w;
	m_pRect->bottom		= _y + _h;
}

void Sprite::SetCenter(float _x, float _y)
{
	if(!m_pCenter)
		m_pCenter = new D3DXVECTOR2;

	m_pCenter->x = _x;
	m_pCenter->y = _y;
}

void Sprite::SetRotation(float _rotation)
{
	m_fRotation = _rotation;
}

void Sprite::SetScaleCenter(float _x, float _y)
{
	if(!m_pScaleCenter)
		m_pScaleCenter = new D3DXVECTOR2;

	m_pScaleCenter->x = _x;
	m_pScaleCenter->y = _y;
}

void Sprite::SetScale(float _x, float _y)
{
	if(!m_pScale)
		m_pScale = new D3DXVECTOR2;

	m_pScale->x = _x;
	m_pScale->y = _y;
}

void Sprite::SetColor(UCHAR _r, UCHAR _g, UCHAR _b, UCHAR _a)
{
	m_Color = D3DCOLOR_ARGB(_a, _r, _g, _b);
}

void Sprite::GetPosition(float *_x, float *_y)
{
	*_x = m_Position.x;
	*_y = m_Position.y;
}