#ifndef CHAR_INFO_LOADOUT_SUBPANEL_H
#define CHAR_INFO_LOADOUT_SUBPANEL_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Panel.h>
#include <vgui_controls/PropertyPage.h>
#include "tf_controls.h"

using namespace vgui;

class CCharInfoLoadoutSubPanel : public vgui::PropertyPage
{
private:
	DECLARE_CLASS_SIMPLE( CCharInfoLoadoutSubPanel, vgui::PropertyPage );

public:
	CCharInfoLoadoutSubPanel( vgui::Panel *parent );
	virtual void ApplySchemeSettings( IScheme *pScheme );
};

#endif