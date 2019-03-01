#ifndef CHAR_INFO_PANEL_H
#define CHAR_INFO_PANEL_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Panel.h>
#include <vgui_controls/PropertyDialog.h>
#include <vgui_controls/Image.h>
#include <vgui/ISurface.h>
#include "tf_statsummary.h"
#include "charinfo_loadout_subpanel.h"

using namespace vgui;

class CCharacterInfoPanel : public vgui::PropertyDialog
{
private:
	DECLARE_CLASS_SIMPLE( CCharacterInfoPanel, vgui::PropertyDialog );

public:
	CCharacterInfoPanel( vgui::Panel *parent );
	virtual void ApplySchemeSettings( IScheme *pScheme );
	virtual void OpenEconUI( int nUI, bool bUnknown );
	virtual void ShowPanel( bool bShow );
	virtual void OnCommand( const char* command );

private:
	CCharInfoLoadoutSubPanel *m_pChrInfLoadout;
	CTFStatsSummaryPanel *m_pStatsSummary;
};

class CImageButton : public vgui::Button
{
public:
	DECLARE_CLASS_SIMPLE( CImageButton, Button );

	CImageButton( vgui::Panel *parent, const char *name ) : Button( parent, name, "" ) { m_pActiveImage = NULL;m_pInactiveImage = NULL; };
		
	virtual void ApplySettings( KeyValues *inResourceData );
	virtual void ApplySchemeSettings( vgui::IScheme *pScheme );
	virtual void OnSizeChanged( int newWide, int newTall );

	void SetActiveImage( const char *imagename );
	void SetInactiveImage( const char *imagename );
	void SetActiveImage( vgui::IImage *image );
	void SetInactiveImage( vgui::IImage *image );

	virtual void Paint();

private:
	vgui::IImage *m_pActiveImage;
	char *m_pszActiveImageName;

	vgui::IImage *m_pInactiveImage;
	char *m_pszInactiveImageName;

	bool m_bScaleImage;
};

#endif