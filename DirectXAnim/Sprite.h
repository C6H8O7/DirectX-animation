/**
 * Header Sprite
 * 
 * @author  Fabsther
 * @since   03/05/2010
 * @version 1.0
 */

#ifndef SPRITE__H
#define SPRITE__H

#include <d3dx9.h>
#include <d3dx9tex.h>
#include "helper.h"

class Sprite
{
	public:

		LPD3DXSPRITE m_pSprite;
		LPDIRECT3DTEXTURE9 m_pTexture;
		RECT *m_pRect;
		D3DXVECTOR2 *m_pCenter;
		float m_fRotation;
		D3DXVECTOR2 *m_pScaleCenter;
		float m_fScaleRotation;
		D3DXVECTOR2 *m_pScale;
		D3DXVECTOR2 m_Position;
		D3DCOLOR m_Color;

		LPDIRECT3DDEVICE9 m_pD3DDevice;

	public:

		Sprite( LPDIRECT3DDEVICE9 _Device );
		~Sprite();
		void Display();
		
		void SetPosition(float _x, float _y);
		void SetTexture(LPDIRECT3DTEXTURE9 _pTexture);
		void SetRectangle(LONG _x, LONG _y, LONG _w, LONG _h);
		void SetCenter(float _x, float _y);
		void SetRotation(float _rotation);
		void SetScaleCenter(float _x, float _y);
		void SetScale(float _x, float _y);
		void SetColor(UCHAR _r, UCHAR _g, UCHAR _b, UCHAR _a);

		void GetPosition(float *_x, float *_y);
};

#endif //SPRITE__H