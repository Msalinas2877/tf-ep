//========= Copyright © 1996-2006, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef TF_CLASSMENU_H
#define TF_CLASSMENU_H
#ifdef _WIN32
#pragma once
#endif

#include <classmenu.h>
#include <vgui_controls/EditablePanel.h>
#include "vgui_controls/KeyRepeat.h"
#include <filesystem.h>
#include <tf_shareddefs.h>
#include "cbase.h"
#include "tf_controls.h"
#include "tf_gamerules.h"
#include "basemodelpanel.h"
#include "imagemouseoverbutton.h"
#include "IconPanel.h"
#include <vgui_controls/CheckButton.h>
#include "GameEventListener.h"
#include "c_tf_playerresource.h"

using namespace vgui;

#define CLASS_COUNT_IMAGES	11

//-----------------------------------------------------------------------------
// This is the entire info panel for the specific class
//-----------------------------------------------------------------------------
class CTFClassInfoPanel : public vgui::EditablePanel
{
private:
	DECLARE_CLASS_SIMPLE( CTFClassInfoPanel, vgui::EditablePanel );

public:
	CTFClassInfoPanel( vgui::Panel *parent, const char *panelName ) : vgui::EditablePanel( parent, panelName )
	{
	}

	virtual void SetVisible( bool state )
	{
		CModelPanel *pModelPanel = dynamic_cast<CModelPanel *>(FindChildByName( "classModel" ) );
		if ( pModelPanel )
		{
			pModelPanel->SetPanelDirty();

			if ( !state )
			{
				// stop the panel from running any VCD data
				pModelPanel->DeleteVCDData();
			}
		}

		CExRichText *pRichText = dynamic_cast<CExRichText *>(FindChildByName( "classInfo" ) );
		if ( pRichText )
		{
			pRichText->InvalidateLayout( true, false );
		}

		BaseClass::SetVisible( state );
	}
};

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
class CTFClassMenu : public CClassMenu
{
private:
	DECLARE_CLASS_SIMPLE( CTFClassMenu, CClassMenu );

public:
	CTFClassMenu( IViewPort *pViewPort );

	virtual void Update( void );
	virtual Panel *CreateControlByName( const char *controlName );
	virtual void OnTick( void );
	virtual void PaintBackground( void );
	virtual void SetVisible( bool state );
	virtual void PerformLayout();

	MESSAGE_FUNC_CHARPTR( OnShowPage, "ShowPage", page );
	CON_COMMAND_MEMBER_F( CTFClassMenu, "join_class", Join_Class, "Send a joinclass command", 0 );

	virtual void OnClose();
	virtual void OnCommand( const char* cmd );
	virtual void ShowPanel( bool bShow );
	virtual void UpdateClassCounts( void ){}

protected:
	virtual void ApplySchemeSettings( IScheme *pScheme );
	virtual void OnKeyCodePressed( KeyCode code );
	virtual void OnKeyCodeReleased( vgui::KeyCode code );
	virtual void OnThink();
	virtual void UpdateNumClassLabels( int iTeam );
	virtual int	GetTeamNumber() = 0;

protected:

	CExImageButton *m_pClassButtons[TF_CLASS_MENU_BUTTONS];
	CTFClassInfoPanel *m_pClassInfoPanel;

private:

#ifdef _X360
	CTFFooter		*m_pFooter;
#endif

	ButtonCode_t	m_iClassMenuKey;
	int				m_iCurrentClassIndex;
	vgui::CKeyRepeatHandler	m_KeyRepeat;

#ifndef _X360
	CTFImagePanel *m_ClassCountImages[CLASS_COUNT_IMAGES];
	CExLabel *m_pCountLabel;
#endif
};

//-----------------------------------------------------------------------------
// Purpose: Draws the blue class menu
//-----------------------------------------------------------------------------

class CTFClassMenu_Blue : public CTFClassMenu
{
private:
	DECLARE_CLASS_SIMPLE( CTFClassMenu_Blue, CTFClassMenu );

public:
	CTFClassMenu_Blue( IViewPort *pViewPort ) : BaseClass( pViewPort )	{};

	virtual const char *GetName( void )
	{ 
		return PANEL_CLASS_BLUE; 
	}

	virtual int GetTeamNumber( void )
	{
		return TF_TEAM_BLUE;
	}

	virtual void UpdateClassCounts( void ){ UpdateNumClassLabels( TF_TEAM_BLUE ); }
};

//-----------------------------------------------------------------------------
// Purpose: Draws the red class menu
//-----------------------------------------------------------------------------

class CTFClassMenu_Red : public CTFClassMenu
{
private:
	DECLARE_CLASS_SIMPLE( CTFClassMenu_Red, CTFClassMenu );

public:
	CTFClassMenu_Red( IViewPort *pViewPort ) : BaseClass( pViewPort )	{};

	virtual const char *GetName( void )
	{ 
		return PANEL_CLASS_RED;
	}

	virtual int GetTeamNumber( void )
	{
		return TF_TEAM_RED;
	}

	virtual void UpdateClassCounts( void ){ UpdateNumClassLabels( TF_TEAM_RED ); }
};

#endif // TF_CLASSMENU_H

