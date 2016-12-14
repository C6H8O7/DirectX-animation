/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe Transform.
/**************************************************/

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <d3dx9math.h>

class DIRECTXANIMDLL_API Transform
{
	public:

		Transform();
		Transform(Transform& _cpy);
		~Transform();

		void resetComponents();
		
		void setTranslation		(D3DXVECTOR3 _translation);
		void setScale			(D3DXVECTOR3 _scale);
		void setShear			(D3DXVECTOR3 _shear);
		void setRotation		(D3DXQUATERNION _rotation);
		
		LPD3DXVECTOR3			getTranslation();
		LPD3DXVECTOR3			getScale();
		LPD3DXVECTOR3			getShear();
		LPD3DXQUATERNION		getRotation();

		D3DXMATRIXA16			getTransformMatrix();

		void					applyTransform(Transform *_transform);
		void					copyTransform(Transform *_transform);

	private:

		LPD3DXVECTOR3			m_pTranslation;
		LPD3DXVECTOR3			m_pScale;
		LPD3DXVECTOR3			m_pShear;
		LPD3DXQUATERNION		m_pRotation;
};

#endif