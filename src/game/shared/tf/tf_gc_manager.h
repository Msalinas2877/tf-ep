#ifndef TFGC_MANAGER_H
#define TFGC_MANAGER_H
#ifdef _WIN32
#pragma once
#endif
#include "igamesystem.h"
#ifdef CLIENT_DLL
#include "clientsteamcontext.h"
#endif
#include "steam/isteamgamecoordinator.h"
#include "generated_proto/gcsdk_gcmessages.pb.h"
#include "generated_proto/base_gcmessages.pb.h"
#include "generated_proto/gcsystemmsgs.pb.h"
#include "generated_proto/tf_gcmessages.pb.h"

class CTFGCManager : public CAutoGameSystemPerFrame
{
public:
#ifdef GAME_DLL
	CTFGCManager() : m_GCMessageAvalaible( this, &CTFGCManager::Receive ), m_CallbackLogonSuccess( this, &CTFGCManager::OnLogonSuccess ) { m_GCMessageAvalaible.SetGameserverFlag(); }
#else
	CTFGCManager() : m_GCMessageAvalaible( this, &CTFGCManager::Receive ) {};
#endif

	virtual void Send( uint32 uMsgType, google::protobuf::Message* msg );
	STEAM_CALLBACK( CTFGCManager, Receive, GCMessageAvailable_t, m_GCMessageAvalaible );
	virtual void AttemptConnection();
	virtual void Welcome();
#ifdef GAME_DLL
	STEAM_GAMESERVER_CALLBACK( CTFGCManager, OnLogonSuccess, SteamServersConnected_t, m_CallbackLogonSuccess );
	virtual void PreClientUpdate() OVERRIDE;
#endif
private:
	float m_flTimeout = 0.0;
	bool m_bConnected = false;
	bool m_bLoggedOn = false;
};

extern CTFGCManager GCManager;
#endif