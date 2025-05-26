#pragma once
#include "CObj.h"

class CHandle :
    public CObj
{
public:
    CHandle();
    ~CHandle();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public :
    D3DXVECTOR3 Get_Point_World(int i);
private: 
    void PolyToWorld(tagPolygon circleLC, tagPolygon& circleWO);
    void PolyToWorld(tagPolygon circleLC, tagPolygon& circleWO, D3DXVECTOR3 center);
    void KeyCheck();
private:
    D3DXVECTOR3 m_vPos;
    D3DXVECTOR3 m_vRotate;

    D3DXMATRIX worldMat;

    tagPolygon m_tInnerLC;
    tagPolygon m_tOuterLC;
    
    tagPolygon m_tInnerWO;
    tagPolygon m_tOuterWO;
private:
};

