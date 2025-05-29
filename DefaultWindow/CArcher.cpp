#include "pch.h"
#include "CArcher.h"
#include "CKeyMgr.h"
#include "CBow.h"

CArcher::CArcher() : m_pBow(nullptr), m_iMaxArrow(0), m_iArrow(0), m_iPoint(0)
{
    /// Body
    ZeroMemory(&m_vBodyPoint, sizeof(m_vBodyPoint));
    ZeroMemory(&m_vOriginBodyPoint, sizeof(m_vOriginBodyPoint));

    /// Leg
    ZeroMemory(&m_tHead, sizeof(m_tHead));
    ZeroMemory(&m_tOriginHead, sizeof(m_tOriginHead));

    /// Head
    ZeroMemory(&m_vLegPoint, sizeof(m_vLegPoint));
    ZeroMemory(&m_vOriginLegPoint, sizeof(m_vOriginLegPoint));

    /// UpperArm
    ZeroMemory(&m_vUpperArmPoint, sizeof(m_vUpperArmPoint));
    ZeroMemory(&m_vOriginUpperArmPoint, sizeof(m_vOriginUpperArmPoint));

    /// ForeArm
    ZeroMemory(&m_vForeArmPoint, sizeof(m_vForeArmPoint));
    ZeroMemory(&m_vOriginForeArmPoint, sizeof(m_vOriginForeArmPoint));
}

CArcher::~CArcher()
{
    Release();
}

void CArcher::Initialize()
{
    m_tInfo.vPos = { 760.f, 400.f, 0.f };
    m_fAngle = 90.f;

    /// Body
    m_vOriginBodyPoint[0] = { -15.f, -5.f, 0.f };
    m_vOriginBodyPoint[1] = {  15.f, -5.f, 0.f };
    m_vOriginBodyPoint[2] = {  15.f,  45.f, 0.f };
    m_vOriginBodyPoint[3] = { -15.f,  45.f, 0.f };

    /// Leg
    m_vOriginLegPoint[0] = m_vOriginBodyPoint[3];
    m_vOriginLegPoint[1] = { m_vOriginBodyPoint[3].x - 5.f, m_vOriginBodyPoint[3].y + 55.f, 0.f };
    m_vOriginLegPoint[2] = { m_vOriginBodyPoint[3].x + 5.f, m_vOriginBodyPoint[3].y + 55.f, 0.f };
    m_vOriginLegPoint[3] = { 0, m_vOriginBodyPoint[3].y, 0.f };
    m_vOriginLegPoint[4] = { m_vOriginBodyPoint[2].x - 5.f, m_vOriginBodyPoint[2].y + 55.f, 0.f };
    m_vOriginLegPoint[5] = { m_vOriginBodyPoint[2].x + 5.f, m_vOriginBodyPoint[2].y + 55.f, 0.f };
    m_vOriginLegPoint[6] = m_vOriginBodyPoint[2];

    /// Head
    m_tOriginHead.m_vCenter = { 0.f, 0.f, 0.f };
    m_tOriginHead.m_vScale = { 15.f, 18.f, 1.f };
    m_tOriginHead.Set_Size(36);
    m_tHead.Set_Size(36);
    m_tOriginHead.SyncToWorld(m_tHead);

    /// UpperArm
    m_vOriginUpperArmPoint[0] = { -5.f, -5.f, 0.f };
    m_vOriginUpperArmPoint[1] = {  5.f, -5.f, 0.f };
    m_vOriginUpperArmPoint[2] = {  5.f,  35.f, 0.f };
    m_vOriginUpperArmPoint[3] = { -5.f,  35.f, 0.f };

    /// ForeArm
    m_vOriginForeArmPoint[0] = { -5.f, -5.f, 0.f };
    m_vOriginForeArmPoint[1] = {  5.f, -5.f, 0.f };
    m_vOriginForeArmPoint[2] = {  5.f,  35.f, 0.f };
    m_vOriginForeArmPoint[3] = { -5.f,  35.f, 0.f };

    m_iMaxArrow = m_iArrow = 5;
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


    /// Leg
    for (int i = 0; i < 7; ++i)
        D3DXVec3TransformCoord(&m_vLegPoint[i], &m_vOriginLegPoint[i], &m_tInfo.matWorld);


    /// Head
    D3DXMatrixScaling(&matScale, m_tOriginHead.m_vScale.x, m_tOriginHead.m_vScale.y, m_tOriginHead.m_vScale.z);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle + 90.f));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y - m_tOriginHead.m_vScale.y - 5.f, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < m_tOriginHead.Size(); ++i)
        D3DXVec3TransformCoord(&m_tHead.m_vPoints[i], &m_tOriginHead.m_vPoints[i], &m_tInfo.matWorld);


    /// Limit Angle
    if (m_fAngle <= 90.f)
        m_fAngle = 90.f;
    else if (m_fAngle >= 160.f)
        m_fAngle = 160.f;


    /// UpperArm 
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

    /// Head
    m_tHead.DrawPolyLine(hDC);

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

    /// 화살 개수, 점수
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
    /// Rotate Angle
    if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
        m_fAngle++;
    else if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
        m_fAngle--;

    /// Fire Arrow
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