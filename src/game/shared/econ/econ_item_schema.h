#ifndef ECON_ITEM_SCHEMA_H
#define ECON_ITEM_SCHEMA_H
#include "tier1/utldict.h"
#include "tier1/utlbuffer.h"
#include "tier1/utlrbtree.h"
#include "tier1/utlmap.h"

#ifdef EXTERN_DLL
#define ECON_EXTERN_CLASS DLL_CLASS_EXPORT
#else
#define ECON_EXTERN_CLASS DLL_CLASS_IMPORT
#endif

class CEconItemDefinition
{
public:
	virtual bool BInitFromKV( KeyValues* kv, CUtlVector< CUtlString >* errorbuffer );
	virtual bool BInitItemMappings( CUtlVector< CUtlString >* errorbuffer ) { return true; }
private:
	KeyValues* m_pKeyValues;
public:
	bool	m_bEnabled;
	const char* m_szName;
	unsigned int m_uIndex;
	const char* m_szItemClass;
	const char* m_szItemName;
	const char* m_szItemTypeName;
	const char* m_szItemDescription;
	int m_nBaseItem;
	const char* m_szItemSlot;
	const char* m_szModelPlayer;
	const char* m_szModelWorld;
	bool m_bAttachToHands;//152
	bool m_bAttachToHandsVmOnly;//153
	bool m_bFlipViewmodel;//154
	bool m_bActAsWearable;//154
	bool m_bActAsWeapon;//156
};

class CEconItemSchema{
public:
	CEconItemSchema()	{ SetDefLessFunc( m_ItemsDefs ); }
	virtual bool BInit( const char* file, const char* path, CUtlVector< CUtlString >*  errorbuffer );
	virtual KeyValues* FindDefitionPrefab( const char* name );
	virtual CEconItemDefinition* GetItemDefinition( int index );
private:
	virtual bool BInitTextBuffer( CUtlBuffer &buffer, CUtlVector< CUtlString >*  errorbuffer );
	virtual bool BInitSchema( KeyValues* schema, CUtlVector< CUtlString >*  errorbuffer );
	virtual bool BPostSchemaInit( CUtlVector< CUtlString >*  errorbuffer );
	virtual bool BInitPrefabs( KeyValues* prefabs, CUtlVector< CUtlString >* errorbuffer );
	virtual bool BInitItems( KeyValues* items, CUtlVector< CUtlString >* errorbuffer );
	virtual bool BInitGameInfo( KeyValues* game_info, CUtlVector< CUtlString >* errorbuffer );
	virtual CEconItemDefinition* CreateEconItemDefinition() { return new CEconItemDefinition; }

	CEconItemDefinition* m_pDefaultItemDef = nullptr;

	KeyValues* m_pSchemaKV;
	CUtlDict<KeyValues*, int> m_Prefabs;
	CUtlMap<int, CEconItemDefinition*> m_ItemsDefs;
};

#endif // ECON_ITEM_SCHEMA_H