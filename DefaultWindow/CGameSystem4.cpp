#include "pch.h"
#include "CGameSystem4.h"
#include "CTimeMgr.h"
CGameSystem4::CGameSystem4() : m_fInputTime(0), m_fResultTime(0)
{
}

CGameSystem4::~CGameSystem4()
{
}

void CGameSystem4::Initialize()
{
	Input_Type();
}

int CGameSystem4::Update()
{
	m_fInputTime += CTimeMgr::Get_Instance()->Get_Delta();
	if (m_fInputTime >= 3.f)
	{
		Input_Type();
		m_fInputTime = 0.f;
	}

	m_fResultTime += CTimeMgr::Get_Instance()->Get_Delta();
	if (m_fResultTime >= 2.f)
	{
		Validate_Result();
		m_fResultTime = -1.f;
	}
	return 0;
}

void CGameSystem4::Late_Update()
{
}

void CGameSystem4::Render(HDC hDC)
{
	if (!q.empty())
	{
		std::pair<BTYPE, WTYPE> eType = q.front();
		switch (eType.first)
		{
		case BU:
			TextOut(hDC, 100, 30, L"청기들어", 4);
			break;

		case BD:
			TextOut(hDC, 100, 30, L"청기내려", 4);
			break;
		}
		
		switch (eType.second)
		{
		case WU:
			TextOut(hDC, 100, 50, L"백기들어", 4);
			break;

		case WD:
			TextOut(hDC, 100, 50, L"백기내려", 4);
			break;
		}
		
	}
	if (m_fResultTime > 0.f) return;

	if (m_bResult)
	{
		//동그라미 렌더
		TextOut(hDC, 100, 100, L"O", 1);
	}
	else
	{
		TextOut(hDC, 100, 100, L"X", 1);
		//X렌더
	}
}

void CGameSystem4::Release()
{
}

void CGameSystem4::Input_Type()
{
	int _iBType(0), _iWType(0);
	while (true)
	{
		_iBType = rand() % (BTYPE::BEND + 1);
		_iWType = rand() % (WTYPE::WEND + 1);

		if (_iBType == BEND && _iWType == WEND)
			continue;
		else
			break;
	}
	q.push({(BTYPE)_iBType, (WTYPE)_iWType});
}

void CGameSystem4::Validate_Result()
{
	if (q.empty()) return;

	std::pair<BTYPE, WTYPE> eType = q.front();
	q.pop();

	if (m_eCurPlayerBType == eType.first
		&& m_eCurPlayerWType == eType.second)
	{
		m_bResult = true;
		return;
	}
	else
		m_bResult = false;
}
