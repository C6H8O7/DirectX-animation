/**************************************************/
/*		@Author	: Marco
/*		@Date	: 30 / 01 / 2015
/*		@Desc	: Header de la classe Key.
/**************************************************/

#ifndef _KEY_H_
#define _KEY_H_

class DIRECTXANIMDLL_API Key : public Transform
{
	public:

		Key(float _time);
		~Key();

		float getTime();
		void setTime(float _time);

		static void Interpolate(Transform *_tOut, Key *_k1, Key *_k2, float _t);

	private:

		float m_fTime;
};

#endif