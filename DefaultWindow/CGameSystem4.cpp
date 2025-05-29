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
	SelectBString = L"";
	SelectWString = L"";

	TypeString.insert({ "청기들어",L"백기 들지 말고 청기들어" });
	TypeString.insert({ "청기들어",L"청기들어" });
	TypeString.insert({ "청기들어",L"청기 내리지 말고 청기들어" });

	TypeString.insert({ "청기내려",L"백기 내리지 말고 청기내려" });
	TypeString.insert({ "청기내려",L"청기내려" });
	TypeString.insert({ "청기내려",L"청기 들지 말고 청기내려" });

	TypeString.insert({ "백기들어",L"청기 들지 말고 백기들어" });
	TypeString.insert({ "백기들어",L"백기들어" });
	TypeString.insert({ "백기들어",L"백기 내리지 말고 백기들어" });

	TypeString.insert({ "백기내려",L"백기 들지 말고 백기내려" });
	TypeString.insert({ "백기내려",L"청기 내리지 말고 백기내려" });
	TypeString.insert({ "백기내려",L"백기내려" });

	m_fInputTime = 0;
	m_fResultTime = 0;

	Input_Type();

	Circle[0].LPoly.m_vScale = D3DXVECTOR3(160.f, 160.f, 60.f);
	Circle[1].LPoly.m_vScale = D3DXVECTOR3(140.f, 140.f, 60.f);

	for (int i = 0; i < 2; ++i)
	{
		Circle[i].LPoly.m_vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
		Circle[i].LPoly.Set_Size(50);
	}

	m_vPoint[0] = { -200,10,0 };
	m_vPoint[1] = { -200,-10,0 };
	m_vPoint[2] = { 200,-10,0 };
	m_vPoint[3] = { 200,10,0 };
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
	for(int i =0; i<2; ++i)
	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, Circle[i].LPoly.m_vScale.x, Circle[i].LPoly.m_vScale.y, Circle[i].LPoly.m_vScale.z);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.0f);

		Circle[i].matWorld = matScale * matRotZ * matTrans;

		Circle[i].WPoly.Set_Size(50);
		for (int j = 0; j < Circle[i].LPoly.Size(); ++j)
		{
			D3DXVec3TransformCoord(&Circle[i].WPoly.m_vPoints[j], &Circle[i].LPoly.m_vPoints[j], &Circle[i].matWorld);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		D3DXMATRIX matScale, matRotZ, matRotZ2, matTrans;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

		D3DXMatrixRotationZ(&matRotZ, 45.f);
		D3DXMatrixRotationZ(&matRotZ2, -45.f);

		D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.0f);

		m_tInfo.matWorld = matScale * matRotZ * matTrans;

		XMatrix = matScale * matRotZ2 * matTrans;
		for (int j = 0; j < 4; ++j)
		{
			D3DXVec3TransformCoord(&m_vOrigin[j], &m_vPoint[j], &m_tInfo.matWorld);
			D3DXVec3TransformCoord(&m_vOrigin2[j], &m_vPoint[j], &XMatrix);
		}
	}
}

void CGameSystem4::Render(HDC hDC)
{
	if (!q.empty())
	{
		TextOut(hDC, 100, 25, SelectBString.c_str(), SelectBString.length());
		TextOut(hDC, 100, 50, SelectWString.c_str(), SelectWString.length());
	}
	if (m_fResultTime >= 0.f) return;

	if (m_bResult)
	{
		//동그라미 렌더
		HBRUSH hBrushBlue = CreateSolidBrush(RGB(65, 105, 225));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushBlue);
		Circle[0].WPoly.DrawPolygon(hDC);
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrushBlue);
		Circle[1].WPoly.DrawPolygon(hDC);
	}
	else
	{
		vector<POINT> pts;
		vector<POINT> pts2;
		for (const auto& v : m_vOrigin) 
		{
			pts.push_back({ LONG(v.x), LONG(v.y) });
		}
		for (const auto& v : m_vOrigin2)
		{
			pts2.push_back({ LONG(v.x), LONG(v.y) });
		}
		HBRUSH hBrushRed = CreateSolidBrush(RGB(206, 0, 24));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushRed);
		Polygon(hDC, pts.data(), static_cast<int>(pts.size()));
		Polygon(hDC, pts2.data(), static_cast<int>(pts2.size()));
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrushRed);
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
	Select_String((BTYPE)_iBType, (WTYPE)_iWType);
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

void CGameSystem4::Select_String(BTYPE btype, WTYPE wtype)
{
	switch (btype)
	{
	case BU:
	{
		auto range = TypeString.equal_range("청기들어");
		int count = std::distance(range.first, range.second);

		if (count > 0) {
			int randIndex = rand() % count;
			auto it = range.first;
			std::advance(it, randIndex);

			SelectBString = it->second;
		}
		break;
	}	
	case BD:
	{
		auto range = TypeString.equal_range("청기내려");

		int count = std::distance(range.first, range.second);

		if (count > 0) {
			int randIndex = rand() % count;
			auto it = range.first;
			std::advance(it, randIndex);

			SelectBString = it->second;
		}
		break;
	}
	default:
		SelectBString = L"";
	}

	switch (wtype)
	{
	case BU:
	{
		auto range = TypeString.equal_range("백기들어");
		int count = std::distance(range.first, range.second);

		if (count > 0) {
			int randIndex = rand() % count;
			auto it = range.first;
			std::advance(it, randIndex);

			SelectWString = it->second;
		}
		break;
	}
	case BD:
	{
		auto range = TypeString.equal_range("백기내려");

		int count = std::distance(range.first, range.second);

		if (count > 0) {
			int randIndex = rand() % count;
			auto it = range.first;
			std::advance(it, randIndex);

			SelectWString = it->second;
		}
		break;
	}
	default:
		SelectWString = L"";
	}
}
