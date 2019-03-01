#ifndef ECON_ITEM_H
#define ECON_ITEM_H

struct wearableanimplayback_t
{
	int iStub;
};

class CAttributeList
{
public:
//	DECLARE_PREDICTABLE();
	DECLARE_CLASS_NOBASE( CAttributeList );
	DECLARE_EMBEDDED_NETWORKVAR();
};
#endif