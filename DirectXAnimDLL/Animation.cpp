#include "stdafx.h"

Animation::Animation(std::string _name, float _length)
	: m_strName(_name), m_fLength(_length)
{
	m_TrackArray = new Array();
	InitArray(m_TrackArray);
}

Animation::~Animation()
{
	delete m_TrackArray;
}

std::string Animation::getName()
{
	return m_strName;
}

float Animation::getLength()
{
	return m_fLength;
}

void Animation::addTrack(Track *_track)
{
	PushBackArray(m_TrackArray, _track);
}

Track *Animation::findTrack(std::string _boneName)
{
	Track **tracks = (Track**)m_TrackArray->data;

	for(int i=0; i<m_TrackArray->size; i++)
	{
		Track *track = tracks[i];

		if(track->getBoneName() == _boneName)
			return track;
	}

	return 0;
}