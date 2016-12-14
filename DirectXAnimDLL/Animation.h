/**************************************************/
/*		@Author	: Marco
/*		@Date	: 13 / 01 / 2015
/*		@Desc	: Header de la classe Animation.
/**************************************************/

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

class DIRECTXANIMDLL_API Animation
{
	public:

		Animation(std::string _name, float _length);
		~Animation();

		std::string getName();

		float getLength();

		void addTrack(Track *_track);

		Track *findTrack(std::string _boneName);

	private:

		std::string m_strName;

		float m_fLength;

		Array* m_TrackArray;
};

#endif