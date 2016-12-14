/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe Skeleton.
/**************************************************/

#ifndef _SKELETON_H_
#define _SKELETON_H_

class DIRECTXANIMDLL_API Skeleton
{
	public:

		Skeleton();
		~Skeleton();

		Pose*	getPosePtr();

	private:

		Pose*	m_pPose;
};

#endif