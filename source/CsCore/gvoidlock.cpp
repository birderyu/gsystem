#include "gvoidlock.h"

gbool GVoidLock::Lock()
{
	return true;
}

gbool GVoidLock::Trylock()
{
	return true;
}

gvoid GVoidLock::Unlock()
{
	
}
