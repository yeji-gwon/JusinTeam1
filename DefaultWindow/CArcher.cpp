#include "pch.h"
#include "CArcher.h"
#include "CKeyMgr.h"
#include "CBow.h"

CArcher::CArcher() : m_pBow(nullptr), m_iMaxArrow(0), m_iArrow(0), m_iPoint(0)
{
    ZeroMemory(&m_vBodyPoint, sizeof(m_vBodyPoint));
    ZeroMemory(&m_vOriginBodyPoint, sizeof(m_vOriginBodyPoint));
    ZeroMemory(&m_vUpperArmPoint, sizeof(m_vUpperArmPoint));
    ZeroMemory(&m_vOriginUpperArmPoint, sizeof(m_vOriginUpperArmPoint));
    ZeroMemory(&m_vForeArmPoint, sizeof(m_vForeArmPoint));
    ZeroMemory(&m_vOriginForeArmPoint, sizeof(m_vOriginForeArmPoint));
    ZeroMemory(&m_vLegPoint, sizeof(m_vLegPoint));
    ZeroMemory(&m_vOriginLegPoint, sizeof(m_vOriginLegPoint));
}

CArcher::~CArcher()
{
    Release();
}

void CArcher::Initialize()
{
    m_tInfo.vPos = { 760.f, 400.f, 0.f };

    m_fAngle = 90.f;

    m_vOriginBodyPoint[0] = { -15.f, -5.f, 0.f };
    m_vOriginBodyPoint[1] = {  15.f, -5.f, 0.f };
    m_vOriginBodyPoint[2] = {  15.f,  45.f, 0.f };
    m_vOriginBodyPoint[3] = { -15.f,  45.f, 0.f };

    m_vOriginUpperArmPoint[0] = { -5.f, -5.f, 0.f };
    m_vOriginUpperArmPoint[1] = {  5.f, -5.f, 0.f };
    m_vOriginUpperArmPoint[2] = {  5.f,  35.f, 0.f };
    m_vOriginUpperArmPoint[3] = { -5.f,  35.f, 0.f };

    m_vOriginForeArmPoint[0] = { -5.f, -5.f, 0.f };
    m_vOriginForeArmPoint[1] = {  5.f, -5.f, 0.f };
    m_vOriginForeArmPoint[2] = {  5.f,  35.f, 0.f };
    m_vOriginForeArmPoint[3] = { -5.f,  35.f, 0.f };

    m_vOriginLegPoint[0] = m_vOriginBodyPoint[3];
    m_vOriginLegPoint[1] = { m_vOriginBodyPoint[3].x - 5.f, m_vOriginBodyPoint[3].y + 55.f, 0.f };
    m_vOriginLegPoint[2] = { m_vOriginBodyPoint[3].x + 5.f, m_vOriginBodyPoint[3].y + 55.f, 0.f };
    m_vOriginLegPoint[3] = { 0, m_vOriginBodyPoint[3].y, 0.f };
    m_vOriginLegPoint[4] = { m_vOriginBodyPoint[2].x - 5.f, m_vOriginBodyPoint[2].y + 55.f, 0.f };
    m_vOriginLegPoint[5] = { m_vOriginBodyPoint[2].x + 5.f, m_vOriginBodyPoint[2].y + 55.f, 0.f };
    m_vOriginLegPoint[6] = m_vOriginBodyPoint[2];


    m_iMaxArrow = m_iArrow = 10;
}

int CArcher::Update()
{
    D3DXMATRIX  matScale;
    D3DXMATRIX  matRotZ;
    D3DXMATRIX  matTrans;


    /// Body
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, 0.f);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
        D3DXVec3TransformCoord(&m_vBodyPoint[i], &m_vOriginBodyPoint[i], &m_tInfo.matWorld);
    for (int i = 0; i < 7; ++i)
        D3DXVec3TransformCoord(&m_vLegPoint[i], &m_vOriginLegPoint[i], &m_tInfo.matWorld);


    /// UpperArm
    if (m_fAngle <= 90.f)
        m_fAngle = 90.f;
    else if (m_fAngle >= 160.f)
        m_fAngle = 160.f;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
        D3DXVec3TransformCoord(&m_vUpperArmPoint[i], &m_vOriginUpperArmPoint[i], &m_tInfo.matWorld);


    /// ForeArm
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - 10.f + 30.f * -sinf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.y + 30.f * cosf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
        D3DXVec3TransformCoord(&m_vForeArmPoint[i], &m_vOriginForeArmPoint[i], &m_tInfo.matWorld);


    /// Bow
    if (m_pBow)
    {
        D3DXVECTOR3 vPos = { m_tInfo.vPos.x - 10.f + 30.f * -sinf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.y + 30.f * cosf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.z };
        m_pBow->Set_Pos(vPos);
        m_pBow->Set_Angle(m_fAngle - 90.f);
    }


    /// Key_Input
    Key_Input();


    return 0;
}

void CArcher::Late_Update()
{
}

void CArcher::Render(HDC hDC)
{
    /// Body
    MoveToEx(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y, nullptr);
    for (int i = 0; i < 4; ++i)
        LineTo(hDC, (int)m_vBodyPoint[i].x, (int)m_vBodyPoint[i].y);
    LineTo(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y);

    /// Leg
    MoveToEx(hDC, (int)m_vLegPoint[0].x, (int)m_vLegPoint[0].y, nullptr);
    for (int i = 0; i < 7; ++i)
        LineTo(hDC, (int)m_vLegPoint[i].x, (int)m_vLegPoint[i].y);
    LineTo(hDC, (int)m_vLegPoint[0].x, (int)m_vLegPoint[0].y);

    /// UpperArm
    MoveToEx(hDC, (int)m_vUpperArmPoint[0].x, (int)m_vUpperArmPoint[0].y, nullptr);
    for (int i = 0; i < 4; ++i)
        LineTo(hDC, (int)m_vUpperArmPoint[i].x, (int)m_vUpperArmPoint[i].y);
    LineTo(hDC, (int)m_vUpperArmPoint[0].x, (int)m_vUpperArmPoint[0].y);

    /// ForeArm
    MoveToEx(hDC, (int)m_vForeArmPoint[0].x, (int)m_vForeArmPoint[0].y, nullptr);
    for (int i = 0; i < 4; ++i)
        LineTo(hDC, (int)m_vForeArmPoint[i].x, (int)m_vForeArmPoint[i].y);
    LineTo(hDC, (int)m_vForeArmPoint[0].x, (int)m_vForeArmPoint[0].y);

    /// 화살 개수
    TCHAR szText[32];
    swprintf_s(szText, L"화살 : %d / %d", m_iArrow, m_iMaxArrow);
    TextOut(hDC, 10, 100, szText, lstrlen(szText));
    swprintf_s(szText, L"점수 : %d", m_iPoint);
    TextOut(hDC, 10, 120, szText, lstrlen(szText));
}

void CArcher::Release()
{
}

void CArcher::Key_Input()
{
    if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
        m_fAngle++;
    else if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
        m_fAngle--;

    if (m_pBow)
    {
        if (0 >= m_iArrow)
            return;

        if (CKeyMgr::Get_Instance()->Key_Hold(VK_SPACE))
        {
            dynamic_cast<CBow*>(m_pBow)->Add_Offset(1.f); 
        }             
        else if(CKeyMgr::Get_Instance()->Key_Away(VK_SPACE))
        { 
            m_iArrow--;
            dynamic_cast<CBow*>(m_pBow)->Set_Fire();
            dynamic_cast<CBow*>(m_pBow)->Set_Offset(0.f);
        }     
    } 
}