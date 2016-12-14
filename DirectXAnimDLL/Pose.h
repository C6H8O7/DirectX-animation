/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe Pose.
/**************************************************/

#ifndef _POSE_H_
#define _POSE_H_

class DIRECTXANIMDLL_API Pose
{
	public:

		Pose();
		Pose(Pose& _cpy);
		~Pose();

		void addBone			(Bone *_bone);

		Array*					getBoneArray();

		Bone*					findBone(int _id);
		Bone*					findBone(std::string _name);

		Bone*					getRootBone();

		void					calculateWorldInv();

	private:

		Array*					m_BoneArray;
};

#endif