#include "Precompiled.h"

rs::EAXReverbEffect::EAXReverbEffect() {
	rsCheckOpenALError( alEffecti( mEFXEffectID, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB ));
}

rs::EAXReverbEffect::~EAXReverbEffect() {

}

rs::EAXReverbEffect::Preset rs::EAXReverbEffect::GetPreset() {
	return mPreset;
}

void rs::EAXReverbEffect::SetPreset( rs::EAXReverbEffect::Preset preset ) {
	if( preset != rs::EAXReverbEffect::Preset::None ) {
		if( alEffectf && alEffectfv ) {
			EFXEAXREVERBPROPERTIES & properties = gEAXEFXPresets[ preset ];
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_DENSITY, properties.flDensity ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_DIFFUSION, properties.flDiffusion ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_GAIN,	properties.flGain ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_GAINHF, properties.flGainHF ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_GAINLF, properties.flGainHF ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_TIME, properties.flDecayTime ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_HFRATIO, properties.flDecayHFRatio ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_LFRATIO, properties.flDecayLFRatio ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_GAIN, properties.flReflectionsGain ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_DELAY, properties.flReflectionsDelay ));
			rsCheckOpenALError( alEffectfv( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_PAN, &properties.flReflectionsPan[0] ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_GAIN,	properties.flLateReverbGain ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_DELAY, properties.flLateReverbDelay ));
			rsCheckOpenALError( alEffectfv( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_PAN, &properties.flLateReverbPan[0] ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_ECHO_TIME, properties.flEchoTime ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_ECHO_DEPTH, properties.flEchoDepth ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_MODULATION_TIME, properties.flModulationTime ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_MODULATION_DEPTH, properties.flModulationDepth ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, properties.flAirAbsorptionGainHF ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_HFREFERENCE, properties.flHFReference ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_LFREFERENCE, properties.flLFReference ));
			rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, properties.flRoomRolloffFactor ));
		}
	}
}

void rs::EAXReverbEffect::SetRoomRolloffFactor( float roomRolloffFactor ) {
	if( alEffectf ) {
		rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, roomRolloffFactor ));
	}
}

float rs::EAXReverbEffect::GetRoomRolloffFactor() const {
	float roomRolloffFactor = 0.0f;
	if( alGetEffectf ) {
		rsCheckOpenALError( alGetEffectf( mEFXEffectID, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, &roomRolloffFactor ));
	}
	return roomRolloffFactor;
}

void rs::EAXReverbEffect::SetLowFrequencyReference( float lfReference ) {
	if( alEffectf ) {
		rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_LFREFERENCE, lfReference ));
	}
}

float rs::EAXReverbEffect::GetLowFrequencyReference() const {
	float lfReference = 0.0f;
	if( alGetEffectf ) {
		rsCheckOpenALError( alGetEffectf( mEFXEffectID, AL_EAXREVERB_LFREFERENCE, &lfReference ));
	}
	return lfReference;
}

void rs::EAXReverbEffect::SetHighFrequencyReference( float hfReference ) {
	if( alEffectf ) {
		rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_HFREFERENCE, hfReference ));
	}
}

float rs::EAXReverbEffect::GetHighFrequencyReference() const {
	float hfReference = 0.0f;
	if( alGetEffectf ) {
		rsCheckOpenALError( alGetEffectf( mEFXEffectID, AL_EAXREVERB_HFREFERENCE, &hfReference ));
	}
	return hfReference;
}

void rs::EAXReverbEffect::SetAirAbsorptionHighFrequencyGain( float hfGain ) {
	if( alEffectf ) {
		rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, hfGain ));
	}
}

float rs::EAXReverbEffect::GetAirAbsorptionHighFrequencyGain() const {
	float hfGain = 0.0f;
	if( alGetEffectf ) {
		rsCheckOpenALError( alGetEffectf( mEFXEffectID, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, &hfGain ));
	}
	return hfGain;
}

void rs::EAXReverbEffect::SetModulationDepth( float modulationDepth ) {
	if( alEffectf ) {
		rsCheckOpenALError( alEffectf( mEFXEffectID, AL_EAXREVERB_MODULATION_DEPTH, modulationDepth ));
	}
}

float rs::EAXReverbEffect::GetModulationDepth() const {
	float modDepth = 0.0f;
	if( alGetEffectf ) {
		rsCheckOpenALError( alGetEffectf( mEFXEffectID, AL_EAXREVERB_MODULATION_DEPTH, &modDepth ));
	}
	return modDepth;
}

void rs::EAXReverbEffect::SetModulationTime( float modulationTime ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_MODULATION_TIME, modulationTime );
}

float rs::EAXReverbEffect::GetModulationTime() const {
	float modTime;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_MODULATION_TIME, &modTime );
	return modTime;
}

void rs::EAXReverbEffect::SetEchoDepth( float echoDepth ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_ECHO_DEPTH, echoDepth );
}

float rs::EAXReverbEffect::GetEchoDepth() const {
	float echoDepth;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_ECHO_DEPTH, &echoDepth );
	return echoDepth;
}

void rs::EAXReverbEffect::SetEchoTime( float echoTime ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_ECHO_TIME, echoTime );
}

float rs::EAXReverbEffect::GetEchoTime() const {
	float echoTime;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_ECHO_TIME, &echoTime );
	return echoTime;
}

void rs::EAXReverbEffect::SetLateReverbPan( const rs::Vec3 & lateReverbPan ) {
	float pan[ 3 ] = { lateReverbPan.x, lateReverbPan.y, lateReverbPan.z };
	alEffectfv( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_PAN, pan );
}

rs::Vec3 rs::EAXReverbEffect::GetLateReverbPan() const {
	rs::Vec3 pan;
	alGetEffectfv( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_PAN, &pan.x );
	return pan;
}

void rs::EAXReverbEffect::SetLateReverbDelay( float lateReverbDelay ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_DELAY, lateReverbDelay );
}

float rs::EAXReverbEffect::GetLateReverbDelay() const {
	float lateReverbDelay;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_DELAY, &lateReverbDelay );
	return lateReverbDelay;
}

void rs::EAXReverbEffect::SetLateReverbGain( float lateReverbGain ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_GAIN, lateReverbGain );
}

float rs::EAXReverbEffect::GetLateReverbGain() const {
	float lateReverbGain;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_LATE_REVERB_GAIN, &lateReverbGain );
	return lateReverbGain;
}

void rs::EAXReverbEffect::SetReflectionsPan( const rs::Vec3 & reflectionsPan ) {
	float pan[ 3 ] = { reflectionsPan.x, reflectionsPan.y, reflectionsPan.z };
	alEffectfv( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_PAN, pan );
}

rs::Vec3 rs::EAXReverbEffect::GetReflectionsPan() const {
	rs::Vec3 pan;
	alGetEffectfv( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_PAN, &pan.x );
	return pan;
}

void rs::EAXReverbEffect::SetReflectionsDelay( float reflectionsDelay ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_DELAY, reflectionsDelay );
}

float rs::EAXReverbEffect::GetReflectionsDelay() const {
	float reflDelay;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_DELAY, &reflDelay );
	return reflDelay;
}

void rs::EAXReverbEffect::SetReflectionsGain( float reflectionsGain ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_GAIN, reflectionsGain );
}

float rs::EAXReverbEffect::GetReflectionsGain() const {
	float reflGain;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_REFLECTIONS_GAIN, &reflGain );
	return reflGain;
}

void rs::EAXReverbEffect::SetDecayLowFrequencyRatio( float lfRatio ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_LFRATIO, lfRatio );
}

float rs::EAXReverbEffect::GetDecayLowFrequencyRatio() const {
	float lfRatio;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_LFRATIO, &lfRatio );
	return lfRatio;
}

void rs::EAXReverbEffect::SetDecayHighFrequencyRatio( float hfRatio ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_HFRATIO, hfRatio );
}

float rs::EAXReverbEffect::GetDecayHighFrequencyRatio() const {
	float hfRatio;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_HFRATIO, &hfRatio );
	return hfRatio;
}

void rs::EAXReverbEffect::SetDecayTime( float decayTime ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_TIME, decayTime );
}

float rs::EAXReverbEffect::GetDecayTime() const {
	float decayTime;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_DECAY_TIME, &decayTime );
	return decayTime;
}

void rs::EAXReverbEffect::SetLowFrequencyGain( float lfGain ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_GAINLF, lfGain );
}

float rs::EAXReverbEffect::GetLowFrequencyGain() const {
	float lfGain;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_GAINLF, &lfGain );
	return lfGain;
}

void rs::EAXReverbEffect::SetHighFrequencyGain( float hfGain ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_GAINHF, hfGain );
}

float rs::EAXReverbEffect::GetHighFrequencyGain() const {
	float hfGain;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_GAINHF, &hfGain );
	return hfGain;
}

void rs::EAXReverbEffect::SetGain( float gain ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_GAIN, gain );
}

float rs::EAXReverbEffect::GetGain() const {
	float gain;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_GAIN, &gain );
	return gain;
}

void rs::EAXReverbEffect::SetDiffusion( float diffusion ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_DIFFUSION, diffusion );
}

float rs::EAXReverbEffect::GetDiffusion() const {
	float diffusion;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_DIFFUSION, &diffusion );
	return diffusion;
}

void rs::EAXReverbEffect::SetDensity( float density ) {
	alEffectf( mEFXEffectID, AL_EAXREVERB_DENSITY, density );
}

float rs::EAXReverbEffect::GetDensity() const {
	float density;
	alGetEffectf( mEFXEffectID, AL_EAXREVERB_DENSITY, &density );
	return density;
}
