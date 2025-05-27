#pragma once
#include "CObj.h"
class CJoint : public CObj
{
public:
	CJoint();
	virtual ~CJoint();

public:
	void Set_ParentPtr(CJoint* pParent);
	void Set_Scale(float _sx, float _sy, float _sz);
	void Set_RotZ(float _rz);
	void Set_Trans(float _tx, float _ty, float _tz);
	D3DXVECTOR3* Get_Point() { return m_vPoint; }
public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

private:
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vRot;
	D3DXVECTOR3		m_vTrans;

	D3DXVECTOR3     m_vPoint[4];
	D3DXVECTOR3     m_vOriginPoint[4];
	CObj*			m_pParent;
};

