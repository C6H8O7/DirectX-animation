#include "stdafx.h"

Skeleton::Skeleton()
{
	m_pPose = new Pose();
}

Skeleton::~Skeleton()
{
	delete m_pPose;
}

Pose* Skeleton::getPosePtr()
{
	return m_pPose;
}