#include "Precompiled.h"

rs::Engine::Engine( ) {
	ALCdevice * device = alcOpenDevice( nullptr );
	if( device ) {
		ALCcontext * context = alcCreateContext( device, nullptr );
		if( context ) {
			alcMakeContextCurrent( context );
			if( alcIsExtensionPresent( device, "ALC_EXT_EFX" )) {

			}
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
