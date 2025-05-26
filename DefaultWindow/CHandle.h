#pragma once
#include "CObj.h"
struct tagCirCle {
    D3DXVECTOR3 m_vCenter;
    D3DXVECTOR3 m_vLT;
    D3DXVECTOR3 m_vRB;
    D3DXVECTOR3 m_vRotate;
    D3DXVECTOR3 m_vScale;
};

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

private: 
    void CircleToWorld(tagCirCle circleLC, tagCirCle& circleWO);
private:
    D3DXVECTOR3 m_vPos;
    D3DXMATRIX worldMat;
    tagCirCle m_tInnerLC;
    tagCirCle m_tOuterLC;
    tagCirCle m_tInnerWO;
    tagCirCle m_tOuterWO;
private:
};

