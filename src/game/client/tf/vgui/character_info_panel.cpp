#include "cbase.h"
#include "vgui/IVGui.h"
#include "ienginevgui.h"
#include "vgui_controls/PropertySheet.h"
#include "character_info_panel.h"

vgui::Panel *Create_CImageButton()
{
	return new CImageButton(NULL, "");
}

DECLARE_BUILD_FACTORY_CUSTOM_ALIAS( CImageButton, ImageButton, Create_CImageButton )

void Open_CharInfo();
ConCommand open_charinfo ("open_charinfo", Open_CharInfo, "Open the character info panel");

vgui::PHandle g_CharInfoPanel;

CCharacterInfoPanel* GetCharInfoPanel()
{
	if ( !g_CharInfoPanel.Get() )
	{
		CCharacterInfoPanel *panel = new CCharacterInfoPanel(NULL);
		g_CharInfoPanel.Set(panel);
		g_CharInfoPanel.Get()->MakeReadyForUse();
	}
	return ( CCharacterInfoPanel *)g_CharInfoPanel.Get();
}

void Open_CharInfo()
{
	if ( GetCharInfoPanel() )
		GetCharInfoPanel()->OpenEconUI( 0, false );
}

CCharacterInfoPanel::CCharacterInfoPanel( vgui::Panel *parent ) : vgui::PropertyDialog( parent, "character_info" )
{
	VPANEL GameUiPanel = enginevgui->GetPanel( PANEL_GAMEUIDLL );
	SetParent( GameUiPanel );
	SetAutoDelete( false );
	SetMoveable( false );
	SetSizeable( false );

	HScheme Scheme = g_pVGuiSchemeManager->LoadSchemeFromFileEx( enginevgui->GetPanel(PANEL_CLIENTDLL), "resource/ClientScheme.res", "ClientScheme" );
	SetScheme( Scheme );
	SetProportional( true );

	m_pChrInfLoadout = new CCharInfoLoadoutSubPanel( this );
	m_pChrInfLoadout->AddActionSignalTarget( this );
	m_pStatsSummary = new CTFStatsSummaryPanel();
}

void CCharacterInfoPanel::ApplySchemeSettings( IScheme *pScheme )
{
	BaseClass::ApplySchemeSettings( pScheme );
	LoadControlSettings("Resource/UI/CharInfoPanel.res");
	AddPage(m_pChrInfLoadout, "#Loadout");
	AddPage(m_pStatsSummary, "#Stats");

	SetOKButtonVisible(false);
	SetCancelButtonVisible(false);
}

void CCharacterInfoPanel::OpenEconUI( int nUI, bool bUnknown )
{
	if ( IsLayoutInvalid() )
		MakeReadyForUse();

	engine->ClientCmd_Unrestricted("gameui_activate");
	ShowPanel( true );

}

void CCharacterInfoPanel::ShowPanel( bool bShow )
{
	if ( bShow )
	{
		if ( GetActivePage() == m_pChrInfLoadout )
		{
			g_pVGui->PostMessage( GetActivePage()->GetVPanel(), new KeyValues("ShowPage"), GetVPanel() );
		}
		else
		{
			GetPropertySheet()->SetActivePage( m_pChrInfLoadout );
		}
		Activate();
	}
	else
	{

	}
	if ( IsVisible() )
	{
		if ( !bShow && m_pChrInfLoadout->IsVisible() )
		{
			//m_pChrInfLoadout->OnCharInfoClosing();
		}
	}
}

void CCharacterInfoPanel::OnCommand( const char *command )
{
	if ( V_stricmp( command, "back" ) == 0 )
	{
		Close();
	}
	else
	{
		return BaseClass::OnCommand( command );
	}
}

void CImageButton::ApplySettings( KeyValues *inResourceData )
{
	m_bScaleImage = inResourceData->GetInt( "scaleImage", 0 );

	// Active Image
	m_pszActiveImageName = NULL;

	const char *activeImageName = inResourceData->GetString( "activeimage", "" );
	if ( *activeImageName )
	{
		SetActiveImage( activeImageName );
	}

	// Inactive Image
	m_pszInactiveImageName = NULL;

	const char *inactiveImageName = inResourceData->GetString( "inactiveimage", "" );
	if ( *inactiveImageName )
	{
		SetInactiveImage( inactiveImageName );
	}

	BaseClass::ApplySettings( inResourceData );
}

void CImageButton::ApplySchemeSettings( vgui::IScheme *pScheme )
{
	BaseClass::ApplySchemeSettings( pScheme );

	if ( m_pszActiveImageName && strlen( m_pszActiveImageName ) > 0 )
	{
		SetActiveImage( vgui::scheme()->GetImage( m_pszActiveImageName, m_bScaleImage ) );
	}

	if ( m_pszInactiveImageName && strlen( m_pszInactiveImageName ) > 0 )
	{
		SetInactiveImage( vgui::scheme()->GetImage( m_pszInactiveImageName, m_bScaleImage ) );
	}

	vgui::IBorder *pBorder = pScheme->GetBorder( "NoBorder" );
	SetDefaultBorder( pBorder);
	SetDepressedBorder( pBorder );
	SetKeyFocusBorder( pBorder );

	Color blank(0,0,0,0);
	SetDefaultColor( this->GetButtonFgColor(), blank );
	SetArmedColor( this->GetButtonArmedFgColor(), blank );
	SetDepressedColor( this->GetButtonDepressedFgColor(), blank );
}

void CImageButton::SetActiveImage( const char *imagename )
{
	int len = Q_strlen( imagename ) + 1;
	m_pszActiveImageName = new char[ len ];
	Q_strncpy( m_pszActiveImageName, imagename, len );
}

void CImageButton::SetInactiveImage( const char *imagename )
{
	int len = Q_strlen( imagename ) + 1;
	m_pszInactiveImageName = new char[ len ];
	Q_strncpy( m_pszInactiveImageName, imagename, len );
}

void CImageButton::SetActiveImage( vgui::IImage *image )
{
	m_pActiveImage = image;

	if ( m_pActiveImage )
	{
		int wide, tall;
		if ( m_bScaleImage )
		{
			// scaling, force the image size to be our size
			this->GetSize( wide, tall );
			m_pActiveImage->SetSize( wide, tall );
		}
		else
		{
			// not scaling, so set our size to the image size
			m_pActiveImage->GetSize( wide, tall );
			this->SetSize( wide, tall );
		}
	}

	this->Repaint();
}

void CImageButton::SetInactiveImage( vgui::IImage *image )
{
	m_pInactiveImage = image;

	if ( m_pInactiveImage )
	{
		int wide, tall;
		if ( m_bScaleImage)
		{
			// scaling, force the image size to be our size
			GetSize( wide, tall );
			m_pInactiveImage->SetSize( wide, tall );
		}
		else
		{
			// not scaling, so set our size to the image size
			m_pInactiveImage->GetSize( wide, tall );
			SetSize( wide, tall );
		}
	}

	Repaint();
}

void CImageButton::OnSizeChanged( int newWide, int newTall )
{
	if ( m_bScaleImage )
	{
		// scaling, force the image size to be our size

		if ( m_pActiveImage )
			m_pActiveImage->SetSize( newWide, newTall );

		if ( m_pInactiveImage )
			m_pInactiveImage->SetSize( newWide, newTall );
	}
	BaseClass::OnSizeChanged( newWide, newTall );
}

void CImageButton::Paint()
{
	SetActiveImage( m_pActiveImage );
	SetInactiveImage( m_pInactiveImage );

	if ( IsArmed() )
	{
		// draw the active image
		if ( m_pActiveImage )
		{
			vgui::surface()->DrawSetColor( 255, 255, 255, 255 );
			m_pActiveImage->SetPos( 0, 0 );
			m_pActiveImage->Paint();
		}
	}
	else 
	{
		// draw the inactive image
		if ( m_pInactiveImage )
		{
			vgui::surface()->DrawSetColor( 255, 255, 255, 255 );
			m_pInactiveImage->SetPos( 0, 0 );
			m_pInactiveImage->Paint();
		}
	}
	
	BaseClass::Paint();
}