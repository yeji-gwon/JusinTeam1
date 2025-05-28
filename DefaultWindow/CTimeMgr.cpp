#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
	:m_iFPS(0), m_fDeltaTime(0.f)
{
	ZeroMemory(m_szBuffer, sizeof(m_szBuffer));
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Initialize()
{
	QueryPerformanceFrequency(&m_nFrequency);
	QueryPerformanceCounter(&m_nPrevCnt);
}
void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_nCurCnt);
	LONGLONG CounterDiff = (m_nCurCnt.QuadPart - m_nPrevCnt.QuadPart); // ���� ī���Ϳ� ���� ī������ ����

	m_fDeltaTime = static_cast<float>(CounterDiff) / static_cast<float>(m_nFrequency.QuadPart);

	// ������ ����: ��Ÿ�� �ʹ� ũ�ų� ���� ��� ����
	if (m_fDeltaTime < 0.f) m_fDeltaTime = 0.f;
	if (m_fDeltaTime > 0.1f) m_fDeltaTime = 0.1f;

	// FPS ���� (1�ʸ���)
	m_iFrameCount++;
	m_fFPSTimeAcc += m_fDeltaTime;
	if (m_fFPSTimeAcc >= 1.f)
	{
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
		m_fFPSTimeAcc = 0.f;
	}

	m_nPrevCnt = m_nCurCnt;
}


void CTimeMgr::Late_Update()
{
}

void CTimeMgr::Render(HDC _hDC)
{
	//RECT tmp{ 20,20,400,500 };
	//swprintf_s(m_szBuffer, L"FPS : %d", m_iFPS);
	//DrawText(_hDC, m_szBuffer, lstrlen(m_szBuffer), &tmp, DT_SINGLELINE);
}

void CTimeMgr::Release()
{
}
