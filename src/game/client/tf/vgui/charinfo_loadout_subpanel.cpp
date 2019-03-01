#include "cbase.h"
#include "charinfo_loadout_subpanel.h"

CCharInfoLoadoutSubPanel::CCharInfoLoadoutSubPanel( vgui::Panel *parent ) : vgui::PropertyPage(parent, "CharInfoLoadoutSubPanel")
{
	g_pVGui->AddTickSignal(GetVPanel());
}

void CCharInfoLoadoutSubPanel::ApplySchemeSettings( IScheme *pScheme )
{
	BaseClass::ApplySchemeSettings(pScheme);
	LoadControlSettings("Resource/UI/CharInfoLoadoutSubPanel.res");
	
	if( Panel *pnl = FindChildByName("ShowBackpackButton") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowBackpackLabel") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowCraftingButton") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowCraftingLabel") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowArmoryButton") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowArmoryLabel") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowTradeButton") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowTradeLabel") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowPaintkitsButton") )
		pnl->MarkForDeletion();

	if( Panel *pnl = FindChildByName("ShowPaintkitsLabel") )
		pnl->MarkForDeletion();
}