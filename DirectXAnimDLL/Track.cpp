#include "stdafx.h"

Track::Track(std::string _boneName)
	: m_strBone(_boneName)
{
	m_KeyArray = new Array();
	InitArray(m_KeyArray);
}

Track::~Track()
{
	delete m_KeyArray;
}

void Track::addKey(Key *_key)
{
	PushBackArray(m_KeyArray, _key);
}

std::string Track::getBoneName()
{
	return m_strBone;
}

void Track::findKeys(Key **_k1, Key **_k2, float _t)
{
	Key *lastKey = 0;
	
	*_k1 = 0;
	*_k2 = 0;

	Key** keys = (Key**)m_KeyArray->data;

	for(int i=0; i<m_KeyArray->size; i++)
	{
		Key *key = keys[i];

		if(key->getTime() > _t)
		{
			*_k1 = lastKey;
			*_k2 = key;
			return;
		}

		lastKey = key;
	}
}