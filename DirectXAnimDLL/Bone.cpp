#include "stdafx.h"

Bone::Bone()
	: m_pParent(NULL), m_strParentName("NULL"), m_strName("NULL"), m_iID(-1), m_pOriBone(nullptr)
{
	m_aChilds = new Array();
	InitArray(m_aChilds);
}

Bone::Bone(Bone& _cpy)
	: m_iID(_cpy.getID()), m_strName(_cpy.getName()), m_TLocal(_cpy.getLocalTransform()), m_TWorld(_cpy.getWorldTransform())
{
	m_aChilds = new Array();
	InitArray(m_aChilds);

	m_pParent = nullptr;
	m_strParentName = _cpy.m_strParentName;

	m_pOriBone = &_cpy;
}

Bone::~Bone()
{
	delete m_aChilds;
}

Transform& Bone::getWorldTransform()
{
	return m_TWorld;
}

Transform& Bone::getLocalTransform()
{
	return m_TLocal;
}
		
Transform& Bone::getLerpTransform()
{
	return m_TLerp;
}

void Bone::setParentPtr(Bone *_parent)
{
	m_pParent = _parent;

	if(_parent)
		_parent->addChildPtr(this);
}

void Bone::setParentName(std::string& _name)
{
	m_strParentName = _name;
}

void Bone::setID(int _id)
{
	m_iID = _id;
}

void Bone::setName(std::string _name)
{
	m_strName = _name;
}

Bone* Bone::getParentPtr()
{
	return m_pParent;
}

std::string Bone::getParentName()
{
	return m_strParentName;
}

int Bone::getID()
{
	return m_iID;
}

std::string Bone::getName()
{
	return m_strName;
}

void Bone::addChildPtr(Bone *_child)
{
	PushBackArray(m_aChilds, _child);
}

void Bone::updateWorldTransform(Bone *_parent)
{
	D3DXMATRIXA16 mat;

	if(_parent)
		mat = _parent->getWorldMatrix();
	else
		D3DXMatrixIdentity(&mat);

	D3DXMATRIXA16 childMat;

	D3DXMatrixTransformation(&childMat, 0, 0, m_TLocal.getScale(), 0, m_TLocal.getRotation(), m_TLocal.getTranslation());

	D3DXMatrixMultiply(&m_MWorld, &childMat, &mat);

	D3DXQUATERNION quatRot;
	D3DXVECTOR3 vecScale, vecTrans;

	D3DXMatrixDecompose(&vecScale, &quatRot, &vecTrans, &m_MWorld);

	m_TWorld.setRotation(quatRot);
	
	m_TWorld.setScale(vecScale);

	m_TWorld.setTranslation(vecTrans);

	Bone** childs = (Bone**)m_aChilds->data;

	for(int i=0; i<m_aChilds->size; i++)
	{
		Bone *b = childs[i];

		b->updateWorldTransform(this);
	}
}

D3DXMATRIXA16& Bone::getWorldMatrix()
{
	return m_MWorld;
}

D3DXMATRIXA16& Bone::getWorldIMatrix()
{
	return m_MWorldI;
}

Bone* Bone::getOriBonePtr()
{
	return m_pOriBone;
}