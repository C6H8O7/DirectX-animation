/**************************************************/
/*		@Author	: Marco
/*		@Date	: 03 / 02 / 2015
/*		@Desc	: Header de la classe Clock.
/**************************************************/

#ifndef _CLOCK_H_
#define _CLOCK_H_

class DIRECTXANIMDLL_API Clock
{
	public:

		enum TIME_TYPE
		{
			MS = 1000,
			US = 1000000
		};

		Clock();

		LARGE_INTEGER restart(enum TIME_TYPE _mode);

		float getFPS();

	protected:
		
		LARGE_INTEGER m_liStartingTime;

		LARGE_INTEGER m_liLastStartingTime;

		LARGE_INTEGER m_liFrequency;

		enum TIME_TYPE m_eMode;
		LARGE_INTEGER m_liElapsedTime;
};

#endif