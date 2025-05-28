#pragma once
#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void	Set_Pos(D3DXVECTOR3 vPos) { m_tInfo.vPos = vPos; }
	void	Set_Speed(float fSpeed) { m_fSpeed = fSpeed; }
	void	Set_Angle(float fAngle) { m_fAngle = fAngle; }

	const INFO& Get_Info() const { return m_tInfo; }
	float	Get_Speed() const { return m_fSpeed; }
	float   Get_Angle() const { return m_fAngle; }

public:
	virtual void		Initialize()PURE;
	virtual int			Update()PURE;
	virtual	void		Late_Update()PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release()PURE;

protected:
	INFO		m_tInfo;
	float		m_fSpeed;
	float		m_fAngle;
};