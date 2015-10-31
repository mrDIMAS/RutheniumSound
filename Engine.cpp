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

std::unordered_map<rs::EAXReverbEffect::Preset, EFXEAXREVERBPROPERTIES> gEAXEFXPresets;

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
		ALCcontext * context = alcCreateContext( device, nullptr );
		if( context ) {
			alcMakeContextCurrent( context );
			
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

			InitializeEAXEFXPresets();
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

void rs::Engine::InitializeEAXEFXPresets() {
	EFXEAXREVERBPROPERTIES rp[113] = {
		EFX_REVERB_PRESET_GENERIC, EFX_REVERB_PRESET_PADDEDCELL, EFX_REVERB_PRESET_ROOM, EFX_REVERB_PRESET_BATHROOM, EFX_REVERB_PRESET_LIVINGROOM,	EFX_REVERB_PRESET_STONEROOM, EFX_REVERB_PRESET_AUDITORIUM,
		EFX_REVERB_PRESET_CONCERTHALL, EFX_REVERB_PRESET_CAVE, EFX_REVERB_PRESET_ARENA,	EFX_REVERB_PRESET_HANGAR, EFX_REVERB_PRESET_HALLWAY, EFX_REVERB_PRESET_STONECORRIDOR,
		EFX_REVERB_PRESET_ALLEY, EFX_REVERB_PRESET_FOREST, EFX_REVERB_PRESET_CITY, EFX_REVERB_PRESET_MOUNTAINS, EFX_REVERB_PRESET_QUARRY, EFX_REVERB_PRESET_PLAIN, EFX_REVERB_PRESET_PARKINGLOT, EFX_REVERB_PRESET_SEWERPIPE,
		EFX_REVERB_PRESET_UNDERWATER, EFX_REVERB_PRESET_DRUGGED, EFX_REVERB_PRESET_DIZZY, EFX_REVERB_PRESET_PSYCHOTIC, EFX_REVERB_PRESET_CASTLE_SMALLROOM, EFX_REVERB_PRESET_CASTLE_SHORTPASSAGE, EFX_REVERB_PRESET_CASTLE_MEDIUMROOM,
		EFX_REVERB_PRESET_CASTLE_LONGPASSAGE, EFX_REVERB_PRESET_CASTLE_LARGEROOM, EFX_REVERB_PRESET_CASTLE_HALL, EFX_REVERB_PRESET_CASTLE_CUPBOARD, EFX_REVERB_PRESET_CASTLE_COURTYARD, EFX_REVERB_PRESET_CASTLE_ALCOVE,
		EFX_REVERB_PRESET_FACTORY_ALCOVE, EFX_REVERB_PRESET_FACTORY_SHORTPASSAGE, EFX_REVERB_PRESET_FACTORY_MEDIUMROOM,	EFX_REVERB_PRESET_FACTORY_LONGPASSAGE, EFX_REVERB_PRESET_FACTORY_LARGEROOM,	EFX_REVERB_PRESET_FACTORY_HALL,
		EFX_REVERB_PRESET_FACTORY_CUPBOARD,	EFX_REVERB_PRESET_FACTORY_COURTYARD, EFX_REVERB_PRESET_FACTORY_SMALLROOM, EFX_REVERB_PRESET_ICEPALACE_ALCOVE, EFX_REVERB_PRESET_ICEPALACE_SHORTPASSAGE, EFX_REVERB_PRESET_ICEPALACE_MEDIUMROOM,
		EFX_REVERB_PRESET_ICEPALACE_LONGPASSAGE, EFX_REVERB_PRESET_ICEPALACE_LARGEROOM,	EFX_REVERB_PRESET_ICEPALACE_HALL, EFX_REVERB_PRESET_ICEPALACE_CUPBOARD,	EFX_REVERB_PRESET_ICEPALACE_COURTYARD, EFX_REVERB_PRESET_ICEPALACE_SMALLROOM,
		EFX_REVERB_PRESET_SPACESTATION_ALCOVE, EFX_REVERB_PRESET_SPACESTATION_MEDIUMROOM, EFX_REVERB_PRESET_SPACESTATION_SHORTPASSAGE, EFX_REVERB_PRESET_SPACESTATION_LONGPASSAGE, EFX_REVERB_PRESET_SPACESTATION_LARGEROOM,
		EFX_REVERB_PRESET_SPACESTATION_HALL, EFX_REVERB_PRESET_SPACESTATION_CUPBOARD, EFX_REVERB_PRESET_SPACESTATION_SMALLROOM,	EFX_REVERB_PRESET_WOODEN_ALCOVE, EFX_REVERB_PRESET_WOODEN_SHORTPASSAGE,	EFX_REVERB_PRESET_WOODEN_MEDIUMROOM,
		EFX_REVERB_PRESET_WOODEN_LONGPASSAGE, EFX_REVERB_PRESET_WOODEN_LARGEROOM, EFX_REVERB_PRESET_WOODEN_HALL, EFX_REVERB_PRESET_WOODEN_CUPBOARD,	EFX_REVERB_PRESET_WOODEN_SMALLROOM,	EFX_REVERB_PRESET_WOODEN_COURTYARD,
		EFX_REVERB_PRESET_SPORT_EMPTYSTADIUM, EFX_REVERB_PRESET_SPORT_SQUASHCOURT, EFX_REVERB_PRESET_SPORT_SMALLSWIMMINGPOOL, EFX_REVERB_PRESET_SPORT_LARGESWIMMINGPOOL, EFX_REVERB_PRESET_SPORT_GYMNASIUM,	EFX_REVERB_PRESET_SPORT_FULLSTADIUM,
		EFX_REVERB_PRESET_SPORT_STADIUMTANNOY, EFX_REVERB_PRESET_PREFAB_WORKSHOP, EFX_REVERB_PRESET_PREFAB_SCHOOLROOM, EFX_REVERB_PRESET_PREFAB_PRACTISEROOM, EFX_REVERB_PRESET_PREFAB_OUTHOUSE, EFX_REVERB_PRESET_PREFAB_CARAVAN,
		EFX_REVERB_PRESET_DOME_TOMB, EFX_REVERB_PRESET_PIPE_SMALL, EFX_REVERB_PRESET_DOME_SAINTPAULS, EFX_REVERB_PRESET_PIPE_LONGTHIN, EFX_REVERB_PRESET_PIPE_LARGE, EFX_REVERB_PRESET_PIPE_RESONANT, EFX_REVERB_PRESET_OUTDOORS_BACKYARD,
		EFX_REVERB_PRESET_OUTDOORS_ROLLINGPLAINS, EFX_REVERB_PRESET_OUTDOORS_DEEPCANYON, EFX_REVERB_PRESET_OUTDOORS_CREEK, EFX_REVERB_PRESET_OUTDOORS_VALLEY, EFX_REVERB_PRESET_MOOD_HEAVEN, EFX_REVERB_PRESET_MOOD_HELL,
		EFX_REVERB_PRESET_MOOD_MEMORY, EFX_REVERB_PRESET_DRIVING_COMMENTATOR, EFX_REVERB_PRESET_DRIVING_PITGARAGE, EFX_REVERB_PRESET_DRIVING_INCAR_RACER, EFX_REVERB_PRESET_DRIVING_INCAR_SPORTS, EFX_REVERB_PRESET_DRIVING_INCAR_LUXURY,
		EFX_REVERB_PRESET_DRIVING_FULLGRANDSTAND, EFX_REVERB_PRESET_DRIVING_EMPTYGRANDSTAND, EFX_REVERB_PRESET_DRIVING_TUNNEL, EFX_REVERB_PRESET_CITY_STREETS, EFX_REVERB_PRESET_CITY_SUBWAY,EFX_REVERB_PRESET_CITY_MUSEUM,
		EFX_REVERB_PRESET_CITY_LIBRARY, EFX_REVERB_PRESET_CITY_UNDERPASS, EFX_REVERB_PRESET_CITY_ABANDONED, EFX_REVERB_PRESET_DUSTYROOM, EFX_REVERB_PRESET_CHAPEL, EFX_REVERB_PRESET_SMALLWATERROOM,
	};
	for( int i = 0; i < 113; i++ ) {
		gEAXEFXPresets[static_cast<rs::EAXReverbEffect::Preset>( i )] = rp[i];
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
