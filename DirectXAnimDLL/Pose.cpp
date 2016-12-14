#include "stdafx.h"

Pose::Pose()
{
	m_BoneArray = new Array();
	InitArray(m_BoneArray);
}

Pose::Pose(Pose& _cpy)
{
	m_BoneArray = new Array();
	InitArray(m_BoneArray);

	Array* boneArray = _cpy.m_BoneArray;
	
	Bone** oribones = (Bone**)boneArray->data;

	for(int i=0; i<boneArray->size; i++)
	{
		Bone *b = oribones[i];

		Bone *nb = new Bone(*b);

		addBone(nb);
	}

	Bone** bones = (Bone**)m_BoneArray->data;

	for(int i=0; i<m_BoneArray->size; i++)
	{
		Bone *b = bones[i];

		if(b->getParentName() != "NULL")
			b->setParentPtr(findBone(b->getParentName()));
	}
}

Pose::~Pose()
{
	delete m_BoneArray;
}

void Pose::addBone(Bone *_bone)
{
	PushBackArray(m_BoneArray, _bone);
}

Bone* Pose::findBone(int _id)
{
	Bone** bones = (Bone**)m_BoneArray->data;

	for(int i=0; i<m_BoneArray->size; i++)
	{
		Bone *b = bones[i];

		if(b->getID() == _id)
			return b;
	}

	return 0;
}

Bone* Pose::findBone(std::string _name)
{
	Bone** bones = (Bone**)m_BoneArray->data;

	for(int i=0; i<m_BoneArray->size; i++)
	{
		Bone *b = bones[i];

		if(b->getName() == _name)
			return b;
	}

	return 0;
}

Bone* Pose::getRootBone()
{
	Bone** bones = (Bone**)m_BoneArray->data;

	for(int i=0; i<m_BoneArray->size; i++)
	{
		Bone *b = bones[i];
		
		if(!b->getParentPtr())
			return b;
	}

	return 0;
}

Array* Pose::getBoneArray()
{
	return m_BoneArray;
}

void Pose::calculateWorldInv()
{
	Bone** bones = (Bone**)m_BoneArray->data;

	for(int i=0; i<m_BoneArray->size; i++)
	{
		Bone *b = bones[i];

		D3DXMATRIX& world = b->getWorldMatrix();
		D3DXMATRIX& inv = b->getWorldIMatrix();

		FLOAT d = D3DXMatrixDeterminant(&world);
		D3DXMatrixInverse(&inv, &d, &world);
	}
}