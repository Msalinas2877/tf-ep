#ifndef ECON_ITEM_SYSTEM_H
#define ECON_ITEM_SYSTEM_H

#ifdef _WIN32
#pragma once
#endif

#include "econ_item_schema.h"

//struct baseitemcriteria_t;

class CEconItemSytem
{
public:
	ECON_EXTERN_CLASS void Init( CreateInterfaceFn* factory );
	void ParseItemSchemaFile( const char* file );
	void PostInit() {};
	void ReloadWhitelist() {};
	void ResetAttribStringCache() {};
	void GenerateRandomItem() {};
//	virtual void GenerateBaseItem( baseitemcriteria_t ) {};

	inline CEconItemSchema* GetItemSchema()	{ return m_pItemSchema; }
private:
	CEconItemSchema* m_pItemSchema;

	friend ECON_EXTERN_CLASS CEconItemSytem* ItemSystem();
	bool parsed = false;
};

ECON_EXTERN_CLASS CEconItemSytem* ItemSystem();
ECON_EXTERN_CLASS CEconItemSchema* GetItemSchema();
#endif // ECON_ITEM_SYSTEM_H