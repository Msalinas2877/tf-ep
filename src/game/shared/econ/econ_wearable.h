#ifndef ECON_WEARABLE_H
#define ECON_WEARABLE_H

#ifdef CLIENT_DLL
#define CEconWearalbe C_EconWearalbe
#endif

class CEconWearalbe : public CBaseAnimating
{
public:
	DECLARE_CLASS( CEconEntity, CBaseAnimating );
	DECLARE_NETWORKCLASS();
}
#endif