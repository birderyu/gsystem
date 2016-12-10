#include "CsNullLock.h"

cs_bool CsNullLock::Lock()
{
	return true;
}

cs_bool CsNullLock::Trylock()
{
	return true;
}

cs_void CsNullLock::Unlock()
{
	
}
