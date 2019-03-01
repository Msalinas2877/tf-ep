//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef TF_VIEWMODEL_H
#define TF_VIEWMODEL_H
#ifdef _WIN32
#pragma once
#endif

#include "predictable_entity.h"
#include "utlvector.h"
#include "baseplayer_shared.h"
#include "shared_classnames.h"
#include "tf_weaponbase.h"

#if defined( CLIENT_DLL )
#define CTFViewModel C_TFViewModel
#endif

class CTFViewModel : public CBaseViewModel
{
	DECLARE_CLASS( CTFViewModel, CBaseViewModel );
public:

	DECLARE_NETWORKCLASS();

	CTFViewModel( void );
	virtual ~CTFViewModel( void );

	virtual void CalcViewModelLag( Vector& origin, QAngle& angles, QAngle& original_angles );
	virtual void CalcViewModelView( CBasePlayer *owner, const Vector& eyePosition, const QAngle& eyeAngles );
	virtual void AddViewModelBob( CBasePlayer *owner, Vector& eyePosition, QAngle& eyeAngles );

#if defined( CLIENT_DLL )
	virtual bool ShouldPredict( void )
	{
		if ( GetOwner() && GetOwner() == C_BasePlayer::GetLocalPlayer() )
			return true;

		return BaseClass::ShouldPredict();
	}

	virtual void StandardBlendingRules( CStudioHdr *hdr, Vector pos[], Quaternion q[], float currentTime, int boneMask );
	virtual void ProcessMuzzleFlashEvent( void );

	virtual int GetSkin();
	BobState_t	&GetBobState() { return m_BobState; }

	virtual int DrawModel( int flags );
#endif

private:

#if defined( CLIENT_DLL )

	// This is used to lag the angles.
	CInterpolatedVar<QAngle> m_LagAnglesHistory;
	QAngle m_vLagAngles;
	BobState_t		m_BobState;		// view model head bob state

	CTFViewModel( const CTFViewModel & ); // not defined, not accessible

	QAngle m_vLoweredWeaponOffset;

#endif
};

#ifdef CLIENT_DLL
class C_ViewmodelAttachmentModel : public CBaseAnimating
{
public:
	DECLARE_CLASS( C_ViewmodelAttachmentModel, CBaseAnimating )
	virtual bool InitializeAsClientEntity( const char *pszModelName, RenderGroup_t renderGroup );
	virtual int InternalDrawModel( int flags );
	virtual bool OnPostInternalDrawModel( ClientModelRenderInfo_t *pInfo );
	virtual void StandardBlendingRules( CStudioHdr *pStudioHdr, Vector pos[], Quaternion q[], float currentTime, int boneMask );
	virtual void FormatViewModelAttachment( int nAttachment, matrix3x4_t &attachmentToWorld );
	virtual int GetSkin( void );
	virtual RenderGroup_t GetRenderGroup() { return RENDER_GROUP_VIEW_MODEL_OPAQUE; }

};
#endif

#endif // TF_VIEWMODEL_H
