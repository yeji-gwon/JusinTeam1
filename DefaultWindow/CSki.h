#pragma once
#include "CObj.h"
#include "BoogiDefine.h"
using namespace Boogi;

class CSki :
    public CObj
{
public:
    CSki();
    ~CSki() override;

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Key_Check();
    RECT* Get_Rect();
    float* Get_AnglePt();
    float* Get_LandinfPt();
    void Set_Landed(bool landed);
    int* Get_Count() { return &m_Count; };
private:
    bool m_bLanded;
    int m_Count;
    float m_fRotPer;

    float m_fArmDir;
    float fLandingPoint;
    float fNow_Angle;
    float fPrev_Angle;
    RECT m_SkiFloor;

    D3DXVECTOR3 m_vJump;
    D3DXVECTOR3 m_vCenter;
    D3DXVECTOR3 m_vRotate;
    D3DXVECTOR3 m_vScale;


    tagRectangle m_pLeft;
    tagRectangle m_pRight;
    tagRectangle m_pBody;
    tagPolygon_EX m_Head;

    tagRectangle m_pLeftArm;
    tagRectangle m_pRightArm;
    
    tagRectangle m_pLeftLeg;
    tagRectangle m_pRightLeg;

};

