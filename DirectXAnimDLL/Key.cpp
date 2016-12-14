#include "stdafx.h"

Key::Key(float _time)
	: m_fTime(_time)
{

}

Key::~Key()
{

}

float Key::getTime()
{
	return m_fTime;
}

void Key::setTime(float _time)
{
	m_fTime = _time;
}

void Key::Interpolate(Transform *_tOut, Key *_k1, Key *_k2, float _t)
{
	D3DXMATRIX mat1, mat2;
	D3DXQUATERNION quat1, quat2, quat3;
	D3DXVECTOR3 trans1, trans2, trans3, dummy;
	
	mat1 = _k1->getTransformMatrix();
	mat2 = _k2->getTransformMatrix();
	
	D3DXMatrixDecompose(&dummy, &quat1, &trans1, &mat1);
	D3DXMatrixDecompose(&dummy, &quat2, &trans2, &mat2);

	D3DXVec3Lerp(&trans3, &trans1, &trans2, _t);

	D3DXQuaternionSlerp(&quat3, &quat1, &quat2, _t);

	_tOut->setTranslation(trans3);
	_tOut->setRotation(quat3);
}