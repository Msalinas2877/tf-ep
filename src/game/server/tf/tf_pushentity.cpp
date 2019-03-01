#include "cbase.h"
#include "pushentity.h"

class CTFPhysicsPushedEntities : public CPhysicsPushedEntities
{
public:
	DECLARE_CLASS( CTFPhysicsPushedEntities, CPhysicsPushedEntities )

	virtual bool	SpeculativelyCheckLinearPush( const Vector &vecAbsPush );
};

CTFPhysicsPushedEntities s_TFPushedEntities;
CPhysicsPushedEntities *g_pPushedEntities = &s_TFPushedEntities;

bool CTFPhysicsPushedEntities::SpeculativelyCheckLinearPush( const Vector &vecAbsPush )
{
	return true;
}