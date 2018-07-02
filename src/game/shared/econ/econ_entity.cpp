#include "cbase.h"
#include "econ_entity.h"

IMPLEMENT_NETWORKCLASS_ALIASED( EconEntity, DT_EconEntity )

BEGIN_NETWORK_TABLE( CEconEntity, DT_EconEntity )
#ifdef CLIENT_DLL
	RecvPropDataTable( RECVINFO_DT( m_Item ), 0, &REFERENCE_RECV_TABLE( DT_ScriptCreatedItem ) ),
#else
	SendPropDataTable( SENDINFO_DT( m_Item ), &REFERENCE_SEND_TABLE( DT_ScriptCreatedItem ) ),
#endif
END_NETWORK_TABLE()