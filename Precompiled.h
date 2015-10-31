#ifndef _PRECOMPILED_H_
#define _PRECOMPILED_H_

#include "al.h"
#include "alc.h"
#include "alext.h"
#include "efx-presets.h"
#include "efx.h"
#include "efx-creative.h"

#include "RutheniumSound.h"
#include <vld/include/vld.h>
#include <unordered_map>

extern LPALGENEFFECTS alGenEffects;
extern LPALGENFILTERS alGenFilters;
extern LPALFILTERF alFilterf;
extern LPALFILTERI alFilteri;
extern LPALGETFILTERF alGetFilterf;
extern LPALDELETEEFFECTS alDeleteEffects;
extern LPALISEFFECT	alIsEffect;
extern LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
extern LPALEFFECTI alEffecti;
extern LPALEFFECTF alEffectf;
extern LPALAUXILIARYEFFECTSLOTI	alAuxiliaryEffectSloti;
extern LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
extern LPALEFFECTFV	alEffectfv;
extern LPALGETEFFECTF alGetEffectf;
extern LPALGETEFFECTI alGetEffecti;
extern LPALGETEFFECTFV alGetEffectfv;
extern LPALGETEFFECTIV alGetEffectiv;
void rsCheckOpenALErrorFunc( const char * file, int line, const char * func );

extern std::unordered_map<rs::EAXReverbEffect::Preset, EFXEAXREVERBPROPERTIES> gEAXEFXPresets;

#define rsCheckOpenALError( func ) func; rsCheckOpenALErrorFunc( __FILE__, __LINE__, __FUNCTION__ )

#endif