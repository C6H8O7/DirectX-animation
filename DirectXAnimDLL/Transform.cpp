#include "stdafx.h"

Transform::Transform()
	: m_pTranslation(NULL), m_pScale(NULL), m_pShear(NULL), m_pRotation(NULL)
{

}

Transform::Transform(Transform& _cpy)
	: m_pTranslation(NULL), m_pScale(NULL), m_pShear(NULL), m_pRotation(NULL)
{
	if(_cpy.getTranslation())
		setTranslation(*_cpy.getTranslation());

	if(_cpy.getScale())
		setScale(*_cpy.getScale());

	if(_cpy.getShear())
		setShear(*_cpy.getShear());

	if(_cpy.getRotation())
		setRotation(*_cpy.getRotation());
}

Transform::~Transform()
{
	resetComponents();
}

void Transform::resetComponents()
{
	if(m_pTranslation)
	{
		delete m_pTranslation;
		m_pTranslation = 0;
	}

	if(m_pScale)
	{
		delete m_pScale;
		m_pScale = 0;
	}

	if(m_pShear)
	{
		delete m_pShear;
		m_pShear = 0;
	}

	if(m_pRotation)
	{
		delete m_pRotation;
		m_pRotation = 0;
	}
}
		
void Transform::setTranslation(D3DXVECTOR3 _translation)
{
	if(!m_pTranslation)
		m_pTranslation = new D3DXVECTOR3;

	(*m_pTranslation) = _translation;
}
		
void Transform::setScale(D3DXVECTOR3 _scale)
{
	if(!m_pScale)
		m_pScale = new D3DXVECTOR3;

	(*m_pScale) = _scale;
}
		
void Transform::setShear(D3DXVECTOR3 _shear)
{
	if(!m_pShear)
		m_pShear = new D3DXVECTOR3;

	(*m_pShear) = _shear;
}
		
void Transform::setRotation(D3DXQUATERNION _rotation)
{
	if(!m_pRotation)
		m_pRotation = new D3DXQUATERNION;
	
	(*m_pRotation) = _rotation;
}

LPD3DXVECTOR3 Transform::getTranslation()
{
	return m_pTranslation;
}

LPD3DXVECTOR3 Transform::getScale()
{
	return m_pScale;
}

LPD3DXVECTOR3 Transform::getShear()
{
	return m_pShear;
}

LPD3DXQUATERNION Transform::getRotation()
{
	return m_pRotation;
}

D3DXMATRIXA16 Transform::getTransformMatrix()
{
	D3DXMATRIXA16 mat, matTmp;

	D3DXMatrixIdentity(&mat);

	if(m_pRotation)
	{
		D3DXMatrixRotationQuaternion(&matTmp, m_pRotation);
		mat *= matTmp;
	}

	if(m_pScale)
	{
		D3DXMatrixScaling(&matTmp, m_pScale->x, m_pScale->y, m_pScale->z);
		mat *= matTmp;
	}

	if(m_pTranslation)
	{
		D3DXMatrixTranslation(&matTmp, m_pTranslation->x, m_pTranslation->y, m_pTranslation->z);
		mat *= matTmp;
	}

	return mat;
}

void Transform::applyTransform(Transform *_transform)
{
	D3DXVECTOR3 trans(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 scale(1.0f, 1.0f, 1.0f);

	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	
	if(getTranslation())
		trans += (*getTranslation());

	if(_transform->getTranslation())
		trans += (*_transform->getTranslation());

	if(getScale())
	{
		scale.x *= getScale()->x;
		scale.y *= getScale()->y;
		scale.z *= getScale()->z;
	}

	if(_transform->getScale())
	{
		scale.x *= _transform->getScale()->x;
		scale.y *= _transform->getScale()->y;
		scale.z *= _transform->getScale()->z;
	}

	if(_transform->getRotation())
		rot *= (*_transform->getRotation());

	if(getRotation())
		rot *= (*getRotation());

	setScale(scale);
	setTranslation(trans);
	setRotation(rot);
}

void Transform::copyTransform(Transform *_transform)
{
	resetComponents();
	applyTransform(_transform);
}