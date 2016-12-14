#include "stdafx.h"

Clock::Clock()
{
	QueryPerformanceFrequency(&m_liFrequency);
	QueryPerformanceCounter(&m_liStartingTime);

	m_liLastStartingTime = m_liStartingTime;
}

LARGE_INTEGER Clock::restart(enum TIME_TYPE _mode)
{
	LARGE_INTEGER endingTime;

	m_eMode = _mode;

	QueryPerformanceCounter(&endingTime);

	m_liElapsedTime.QuadPart = endingTime.QuadPart - m_liLastStartingTime.QuadPart;

	m_liElapsedTime.QuadPart *= m_eMode;

	m_liElapsedTime.QuadPart /= m_liFrequency.QuadPart;

	m_liLastStartingTime = endingTime;

	return m_liElapsedTime;
}

float Clock::getFPS()
{
	return (float)m_eMode / m_liElapsedTime.QuadPart;
}