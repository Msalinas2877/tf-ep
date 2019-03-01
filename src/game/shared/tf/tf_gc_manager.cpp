//================================================================================
//
// Purpose:	Communication with the game coordinator, this is not based on the
// actual TF2 code because it is much more complex since is used on a bigger scale
// (Matchmaking, contracts, etc), right now all i care about is the is the player
// inventory
//
//================================================================================

#include "cbase.h"
#include "tf_gc_manager.h"
#include "tf_player.h"

ISteamGameCoordinator* GC = NULL;

//flag used by valve, communication does not work without it
#define PROTOBUFFLAG (1<<31)

void CTFGCManager::Send( uint32 uMsgType, google::protobuf::Message* msg )
{
	ConColorMsg(Color(120, 255, 120, 255), "Sending Message Type: %i\n", uMsgType);
	uMsgType |= PROTOBUFFLAG;
	CUtlMemory<byte> message;
	message.EnsureCapacity( sizeof( uint32 ) * 2 + msg->ByteSize() );

	((uint32*)message.Base())[0] = uMsgType;
	((uint32*)message.Base())[1] = 0;

	msg->SerializeToArray(message.Base() + sizeof( uint32 ) * 2, msg->ByteSize());

	if ( int r = GC->SendMessage(uMsgType, message.Base(), sizeof( uint32 ) * 2 + msg->ByteSize()) != k_EGCResultOK )
		Msg("Error Sending Message!: %d \n", r);
}

void CTFGCManager::Receive( GCMessageAvailable_t* msg )
{
#ifdef GAME_DLL
	uint32 pcubMsgSize;
	while( GC && GC->IsMessageAvailable(&pcubMsgSize) )
	{
		CUtlMemory<byte> incomingmsg;
		incomingmsg.EnsureCapacity( pcubMsgSize );
		uint32 MsgType;

		GC->RetrieveMessage(&MsgType, incomingmsg.Base(),
			incomingmsg.Count(), &pcubMsgSize);
		ConColorMsg(Color(120, 255, 120, 255), "Message: %d\n", MsgType & ~PROTOBUFFLAG );
		switch ((MsgType & ~PROTOBUFFLAG))
		{
		case k_ESOMsg_CacheSubscriptionCheck:
		{
			CMsgSOCacheSubscriptionCheck msgcache;
			msgcache.ParseFromArray( incomingmsg.Base() + sizeof( uint32 ) * 2, incomingmsg.Count() );
			Msg( "%s", msgcache.DebugString().c_str() );
			CMsgSOCacheSubscriptionRefresh msgrefresh;
			msgrefresh.set_owner( msgcache.owner() );
			Send( k_ESOMsg_CacheSubscriptionRefresh, &msgrefresh );
			break;
		}
		case k_ESOMsg_CacheSubscribed:
		{
			CMsgSOCacheSubscribed msgcache;
			msgcache.ParseFromArray( incomingmsg.Base() + sizeof( uint32 ) * 2, incomingmsg.Count() );
			for (int i = 0; i < msgcache.objects_size(); i++)
			{
				if (msgcache.objects( i ).type_id() == 1)
				{
					unsigned short index = g_InventoryManager->m_Player.Find( msgcache.owner() );
					if (index == g_InventoryManager->m_Player.InvalidIndex())
					{
						index = g_InventoryManager->m_Player.Insert( msgcache.owner() );
					}
					for (int o = 0; o < msgcache.objects( i ).object_data_size(); o++)
					{
						CSOEconItem item;
						item.ParseFromString( msgcache.objects( i ).object_data( o ) );
						for (int e = 0; e < item.equipped_state_size(); e++)
						{
							int classindex = item.equipped_state( e ).new_class();
							int slot = item.equipped_state( e ).new_slot();
							g_InventoryManager->m_Player[index].playerclass[classindex].ItemIndex[slot] = item.def_index();
						}
					}
				}
			}
			break;
		}
		case k_EMsgGCServerWelcome:
		{
			Welcome();
			break;
		}
		default:
			break;
		}
	}
#endif
}

void CTFGCManager::AttemptConnection()
{	
	if ( !SteamGameServer()->BLoggedOn() )
	{
		m_bLoggedOn = false;
		m_bConnected = false;
		m_flTimeout = 0.0;
		return;
	}

	if (!m_bConnected)
	{
		// if SteamGameServer()->BLoggedOn() is true and m_bLoggedOn is false, that means we just logged in.
		// in that case a welcome message is sent to us inmediatly (or atleast that happens in game servers, not sure about clients, anyway the code after handles the timeout)
		if ( !m_bLoggedOn )
		{
			m_bLoggedOn = true;
			if ( GC == NULL )
			{
#ifdef CLIENT_DLL
				GC = (ISteamGameCoordinator*)SteamClient()->GetISteamGenericInterface(SteamAPI_GetHSteamUser(), SteamAPI_GetHSteamPipe(), STEAMGAMECOORDINATOR_INTERFACE_VERSION);
#else
				GC = (ISteamGameCoordinator*)SteamGameServerClient()->GetISteamGenericInterface(SteamGameServer_GetHSteamUser(), SteamGameServer_GetHSteamPipe(), STEAMGAMECOORDINATOR_INTERFACE_VERSION);
#endif
			}
			m_flTimeout = Plat_FloatTime() + 2.0;
		}

		// If we do not received a welcome message during the timeout time, send a hello message
		if ( m_flTimeout < Plat_FloatTime() - 30.0 )
		{
			m_flTimeout = Plat_FloatTime();
			ConColorMsg( Color( 120, 255, 120, 255 ), "Attempting connection to Global Coordinator\n" );
			ConColorMsg( Color( 120, 255, 120, 255 ), "Saying Hello\n" );
#ifdef CLIENT_DLL
			CMsgClientHello hello;
			hello.set_version( engine->GetClientVersion() );
			Send( k_EMsgGCClientHello, &hello );
#else
			CMsgServerHello hello;
			hello.set_version( engine->GetServerVersion() );
			Send( k_EMsgGCServerHello, &hello );
#endif
		}
	}
}

#ifdef GAME_DLL
void CTFGCManager::OnLogonSuccess( SteamServersConnected_t *pLogonSuccess )
{
	AttemptConnection();
}

void CTFGCManager::PreClientUpdate()	
{ 
	AttemptConnection();
}
#endif
void CTFGCManager::Welcome()
{
	m_bConnected = true;
	ConColorMsg(Color(120, 255, 120, 255), "Connection Succesfull\n");
	ConColorMsg(Color(120, 255, 120, 255), "Global Coordinator is welcoming us\n");
}

CTFGCManager GCManager;