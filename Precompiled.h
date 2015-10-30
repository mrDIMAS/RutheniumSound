#ifndef _PRECOMPILED_H_
#define _PRECOMPILED_H_

#include "al.h"
#include "alc.h"
#include "efx.h"
#include "EFX-Util.h"
#include "RutheniumSound.h"
#include <vld/include/vld.h>

void rsCheckOpenALErrorFunc( const char * file, int line, const char * func );

#define rsCheckOpenALError( func ) func; rsCheckOpenALErrorFunc( __FILE__, __LINE__, __FUNCTION__ )

#endif