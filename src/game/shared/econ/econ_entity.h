#ifndef ECON_ENTITY_H
#define ECON_ENTITY_H

#include "econ_item.h"
#include "econ_item_system.h"
#include "econ_item_view.h"

#ifdef CLIENT_DLL
#define CEconEntity C_EconEntity
#endif

class CEconEntity : public CBaseAnimating
{
public:
	DECLARE_CLASS( CEconEntity, CBaseAnimating );
	DECLARE_NETWORKCLASS();

	int TranslateViewmodelHandActivity( int iActivity ) { return TranslateViewmodelHandActivityInternal( iActivity ); }
	virtual int TranslateViewmodelHandActivityInternal( int iActivity ) { return iActivity; }
	virtual void PlayAnimForPlaybackEvent( wearableanimplayback_t iPlayback ) {};
#ifdef CLIENT_DLL
	virtual bool WantsToOverrideViewmodelAttachments()	{ return false; }
	virtual bool	OnFireEvent( C_BaseViewModel *pViewModel, const Vector& origin, const QAngle& angles, int event, const char *options ) { return false; }
#endif

	CEconItemView m_Item;
};
#endif