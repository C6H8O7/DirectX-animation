/**************************************************/
/*		@Author	: Marco
/*		@Date	: 30 / 01 / 2015
/*		@Desc	: Header de la classe Track.
/**************************************************/

#ifndef _TRACK_H_
#define _TRACK_H_

class DIRECTXANIMDLL_API Track
{
	public:

		Track(std::string _boneName);
		~Track();

		void addKey(Key *_key);

		std::string getBoneName();

		void findKeys(Key **_k1, Key **_k2, float _t);

	private:

		std::string m_strBone;

		Array* m_KeyArray;
};

#endif