#include "Precompiled.h"

LPALFILTERF	alFilterf;
LPALFILTERI	alFilteri;
LPALEFFECTI	alEffecti;
LPALEFFECTF	alEffectf;
LPALEFFECTFV alEffectfv;
LPALISEFFECT alIsEffect;
LPALGENEFFECTS alGenEffects;
LPALGETFILTERF alGetFilterf;
LPALGENFILTERS alGenFilters;
LPALDELETEEFFECTS alDeleteEffects;
LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
LPALGENAUXILIARYEFFECTSLOTS	alGenAuxiliaryEffectSlots;
LPALDELETEAUXILIARYEFFECTSLOTS	alDeleteAuxiliaryEffectSlots;
LPALGETEFFECTF alGetEffectf;
LPALGETEFFECTI alGetEffecti;
LPALGETEFFECTFV alGetEffectfv;
LPALGETEFFECTIV alGetEffectiv;

rs::Engine::Engine( ) {
	const char * devices = alcGetString( nullptr, ALC_DEVICE_SPECIFIER );
	const char * ptr = devices;
	while( !( *ptr == '\0' && *(ptr + 1) == '\0' ) ) {
		if( *ptr ) {
			std::cout << *ptr;
		} else {
			std::cout << std::endl;
		}
		ptr++;
	}
	ALCdevice * device = alcOpenDevice( nullptr );
	if( device ) {
		if( alcIsExtensionPresent( device, "ALC_EXT_EFX" )) {
			alGenEffects = (LPALGENEFFECTS)alGetProcAddress( "alGenEffects" );
			alGenFilters = (LPALGENFILTERS)alGetProcAddress( "alGenFilters" );
			alFilterf = (LPALFILTERF)alGetProcAddress( "alFilterf" );
			alFilteri = (LPALFILTERI)alGetProcAddress( "alFilteri" );
			alGetFilterf = (LPALGETFILTERF)alGetProcAddress( "alGetFilterf" );
			alDeleteEffects	= (LPALDELETEEFFECTS)alGetProcAddress( "alDeleteEffects" );
			alIsEffect = (LPALISEFFECT)alGetProcAddress( "alIsEffect" );
			alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS)alGetProcAddress( "alGenAuxiliaryEffectSlots" );
			alEffecti = (LPALEFFECTI)alGetProcAddress( "alEffecti" );
			alEffectf = (LPALEFFECTF)alGetProcAddress( "alEffectf" );
			alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress( "alAuxiliaryEffectSloti" );
			alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS)alGetProcAddress( "alDeleteAuxiliaryEffectSlots" );
			alEffectfv = (LPALEFFECTFV)alGetProcAddress( "alEffectfv" );
			alGetEffectf = (LPALGETEFFECTF)alGetProcAddress( "alGetEffectf" );
			alGetEffecti = (LPALGETEFFECTI)alGetProcAddress( "alGetEffecti" );
			alGetEffectfv = (LPALGETEFFECTFV)alGetProcAddress( "alGetEffectfv" );
			alGetEffectiv = (LPALGETEFFECTIV)alGetProcAddress( "alGetEffectiv" );
		}
		ALCcontext * context = alcCreateContext( device, nullptr );
		if( context ) {
			alcMakeContextCurrent( context );
			int iSends = 0;
			alcGetIntegerv( device, ALC_MAX_AUXILIARY_SENDS, 1, &iSends );
			int gfg = 0;
		} else {
			throw std::exception( "Unable to create context" );
		}
	} else {
		throw std::exception( "Unable to open device" );
	}
}

rs::Engine::~Engine() {
	ALCcontext * currentContext = alcGetCurrentContext();
	if( currentContext ) {
		ALCdevice * device = alcGetContextsDevice( currentContext );
		alcMakeContextCurrent( nullptr );
		alcDestroyContext( currentContext );	
		alcCloseDevice(device);
	}	
}

float rs::Engine::GetSpeedOfSound() const {
	return alGetFloat( AL_SPEED_OF_SOUND );
}

void rs::Engine::SetSpeedOfSound( float speedOfSound ) {
	alSpeedOfSound( speedOfSound );
}

float rs::Engine::GetDopplerFactor() const {
	return alGetFloat( AL_DOPPLER_FACTOR );
}

void rs::Engine::SetDopplerFactor( float dopplerFactor ) {
	alDopplerFactor( dopplerFactor );
}

void rs::Engine::SetDistanceModel( rs::Engine::DistanceModel distanceModel ) {
	if( distanceModel == rs::Engine::DistanceModel::None ) {
		alDistanceModel( AL_NONE );
	} else if( distanceModel == rs::Engine::DistanceModel::InverseDistance ) {
		alDistanceModel( AL_INVERSE_DISTANCE );
	} else if( distanceModel == rs::Engine::DistanceModel::InverseDistanceClamped ) {
		alDistanceModel( AL_INVERSE_DISTANCE_CLAMPED );
	} else if( distanceModel == rs::Engine::DistanceModel::LinearDistance ) {
		alDistanceModel( AL_LINEAR_DISTANCE );
	} else if( distanceModel == rs::Engine::DistanceModel::LinearDistanceClamped ) {
		alDistanceModel( AL_LINEAR_DISTANCE_CLAMPED );
	} else if( distanceModel == rs::Engine::DistanceModel::ExponentDistance ) {
		alDistanceModel( AL_EXPONENT_DISTANCE );
	} else if( distanceModel == rs::Engine::DistanceModel::ExponentDistanceClamped ) {
		alDistanceModel( AL_EXPONENT_DISTANCE_CLAMPED );
	};
}

rs::Engine::DistanceModel rs::Engine::GetDistanceModel() const {
	ALenum distanceModel = alGetInteger( AL_DISTANCE_MODEL );
	if( distanceModel == AL_NONE ) {
		return rs::Engine::DistanceModel::None;
	} else if( distanceModel == AL_INVERSE_DISTANCE ) {
		return rs::Engine::DistanceModel::InverseDistance;
	} else if( distanceModel == AL_INVERSE_DISTANCE_CLAMPED ) {
		return rs::Engine::DistanceModel::InverseDistanceClamped;
	} else if( distanceModel == AL_LINEAR_DISTANCE ) {
		return rs::Engine::DistanceModel::LinearDistance;
	} else if( distanceModel == AL_LINEAR_DISTANCE_CLAMPED ) {
		return rs::Engine::DistanceModel::LinearDistanceClamped;
	} else if( distanceModel == AL_EXPONENT_DISTANCE ) {
		return rs::Engine::DistanceModel::ExponentDistance;
	} else if( distanceModel == AL_EXPONENT_DISTANCE_CLAMPED ) {
		return rs::Engine::DistanceModel::ExponentDistanceClamped;
	}
	return rs::Engine::DistanceModel::None;
}
