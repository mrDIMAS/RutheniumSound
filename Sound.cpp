#include "Precompiled.h"

rs::Sound::Sound() : mBufferNum( 0 ), mOALSourceID( 0 ) {
	rsCheckOpenALError( alGenSources( 1, &mOALSourceID ));
}

rs::Sound::Sound( std::shared_ptr<Buffer> buffer ) : mBuffer( buffer ), mOALSourceID( 0 ), mBufferNum( 0 ) {
    rsCheckOpenALError( alGenSources( 1, &mOALSourceID ));

	rs::StreamingBuffer * streamingBuffer = dynamic_cast<rs::StreamingBuffer*>( buffer.get());
	if( streamingBuffer ) {
		rsCheckOpenALError( alSourceQueueBuffers( mOALSourceID, 2, streamingBuffer->GetQueueBuffers()));
	} else {
		rsCheckOpenALError( alSourcei( mOALSourceID, AL_BUFFER, mBuffer->GetOpenALBufferID() ));
	}
}

rs::Sound::~Sound() {
	rsCheckOpenALError( alDeleteSources( 1, &mOALSourceID ));
}

void rs::Sound::AttachToEffectSlot( const std::shared_ptr<rs::EffectSlot> & effectSlot ) {
	mEffectSlot = effectSlot;
	rsCheckOpenALError( alSource3i( mOALSourceID, AL_AUXILIARY_SEND_FILTER, mEffectSlot->GetEFXEffectSlotID(), 0, AL_FILTER_NULL ));
}

void rs::Sound::DetachFromEffectSlot() {
	if( mEffectSlot.get() ) {
		rsCheckOpenALError( alSource3i( mOALSourceID, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, AL_FILTER_NULL ));
		mEffectSlot.reset();
	}
}

void rs::Sound::DoStreaming() {
	rs::StreamingBuffer * streamingBuffer = dynamic_cast<rs::StreamingBuffer*>( mBuffer.get());
	if( streamingBuffer ) {
		unsigned int * oalBuffers = streamingBuffer->GetQueueBuffers();

		int processedBufferCount;
		rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_BUFFERS_PROCESSED, &processedBufferCount ));
		 
		if( processedBufferCount == 1 ) {
			rsCheckOpenALError( alSourceUnqueueBuffers( mOALSourceID, 1, &oalBuffers[ mBufferNum ] ));
			streamingBuffer->DecodeNextBlock( mBufferNum );
			rsCheckOpenALError( alSourceQueueBuffers( mOALSourceID, 1, &oalBuffers[ mBufferNum ] ));
			mBufferNum = 1 - mBufferNum; // flip-flop from 0 to 1
		} else if( processedBufferCount == 2 ) {
			rsCheckOpenALError( alSourceUnqueueBuffers( mOALSourceID, 2, oalBuffers ));
		}
	}
}

bool rs::Sound::IsValid() const {
	return alIsSource( mOALSourceID ) != AL_FALSE;
}

float rs::Sound::GetGain() const {
	float gain;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_GAIN, &gain ));
	return gain;
}

void rs::Sound::SetGain( float gain ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_GAIN, gain ));
}

float rs::Sound::GetPitch() const {
	float pitch;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_PITCH, &pitch ));
	return pitch;
}

void rs::Sound::SetPitch( float pitch ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_PITCH, pitch ));
}

float rs::Sound::GetMaxDistance() const {
	float maxDistance;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_MAX_DISTANCE, &maxDistance ));
	return maxDistance;
}

void rs::Sound::SetMaxDistance( float maxDistance ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_MAX_DISTANCE, maxDistance ));
}

float rs::Sound::GetRolloffFactor() const {
	float rolloffFactor;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_ROLLOFF_FACTOR, &rolloffFactor ));
	return rolloffFactor;
}

void rs::Sound::SetRolloffFactor( float rolloffFactor ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_ROLLOFF_FACTOR, rolloffFactor ));
}

float rs::Sound::GetReferenceDistance() const {
	float referenceDistance;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_REFERENCE_DISTANCE, &referenceDistance ));
	return referenceDistance;
}

void rs::Sound::SetReferenceDistance( float referenceDistance ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_REFERENCE_DISTANCE, referenceDistance ));
}

float rs::Sound::GetMinGain() const {
	float minGain;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_MIN_GAIN, &minGain ));
	return minGain;
}

void rs::Sound::SetMinGain( float minGain ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_MIN_GAIN, minGain ));
}

float rs::Sound::GetMaxGain() const {
	float maxGain;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_MAX_GAIN, &maxGain ));
	return maxGain;
}

void rs::Sound::SetMaxGain( float maxGain ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_MAX_GAIN, maxGain ));
}

float rs::Sound::GetConeOuterGain() const {
	float coneOuterGain;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_CONE_OUTER_GAIN, &coneOuterGain ));
	return coneOuterGain;
}

void rs::Sound::SetConeOuterGain( float coneOuterGain ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_CONE_OUTER_GAIN, coneOuterGain ));
}

float rs::Sound::GetConeInnerAngle() const {
	float coneInnerAngle;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_CONE_INNER_ANGLE, &coneInnerAngle ));
	return coneInnerAngle;
}

void rs::Sound::SetConeInnerAngle( float coneInnerAngle ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_CONE_INNER_ANGLE, coneInnerAngle ));
}

float rs::Sound::GetConeOuterAngle() const {
	float coneOuterAngle;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_CONE_OUTER_ANGLE, &coneOuterAngle ));
	return coneOuterAngle;
}

void rs::Sound::SetConeOuterAngle( float coneOuterAngle ) {
	rsCheckOpenALError( alSourcef( mOALSourceID, AL_CONE_OUTER_ANGLE, coneOuterAngle ));
}

rs::Vec3 rs::Sound::GetPosition() const {
	rs::Vec3 position;
	rsCheckOpenALError( alGetSource3f( mOALSourceID, AL_POSITION, &position.x, &position.y, &position.z ));
	return position;
}

void rs::Sound::SetPosition( const rs::Vec3 & position ) {
	rsCheckOpenALError( alSource3f( mOALSourceID, AL_POSITION, position.x, position.y, position.z ));
}

rs::Vec3 rs::Sound::GetVelocity() const {
	rs::Vec3 velocity;
	rsCheckOpenALError( alGetSource3f( mOALSourceID, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z ));
	return velocity;
}

void rs::Sound::SetVelocity( const rs::Vec3 & velocity ) {
	rsCheckOpenALError( alSource3f( mOALSourceID, AL_VELOCITY, velocity.x, velocity.y, velocity.z ));
}

rs::Vec3 rs::Sound::GetDirection() const {
	rs::Vec3 direction;
	rsCheckOpenALError( alGetSource3f( mOALSourceID, AL_DIRECTION, &direction.x, &direction.y, &direction.z ));
	return direction;
}

void rs::Sound::SetDirection( const rs::Vec3 & direction ) {
	rsCheckOpenALError( alSource3f( mOALSourceID, AL_DIRECTION, direction.x, direction.y, direction.z ));
}

bool rs::Sound::IsPositionRelativeToListener() const {
	int isRelative;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_SOURCE_RELATIVE, &isRelative ));
	return isRelative != 0;
}

void rs::Sound::SetPositionRelativeToListener( bool relativePosition ) {
	rsCheckOpenALError( alSourcei( mOALSourceID, AL_SOURCE_RELATIVE, relativePosition ? AL_TRUE : AL_FALSE ));
}

bool rs::Sound::IsStreaming() const {
	int sourceType;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_SOURCE_TYPE, &sourceType ));
	return sourceType == AL_STREAMING;
}

bool rs::Sound::IsLooping() const {
	int isLooping;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_LOOPING, &isLooping ));
	return isLooping != 0;
}

void rs::Sound::SetLooping( bool looping ) {
	rsCheckOpenALError( alSourcei( mOALSourceID, AL_LOOPING, looping ? AL_TRUE : AL_FALSE ));
}

bool rs::Sound::IsPlaying() const {
	int sourceState;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_SOURCE_STATE, &sourceState ));
	return sourceState == AL_PLAYING;
}

void rs::Sound::Play() {
	rsCheckOpenALError( alSourcePlay( mOALSourceID ));
}

bool rs::Sound::IsStopped() const {
	int sourceState;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_SOURCE_STATE, &sourceState ));
	return sourceState == AL_STOPPED;
}

void rs::Sound::Stop() {
	rsCheckOpenALError( alSourceStop( mOALSourceID ));
}

bool rs::Sound::IsPaused() const {
	int sourceState;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_SOURCE_STATE, &sourceState ));
	return sourceState == AL_PAUSED;
}

void rs::Sound::Pause() {
	rsCheckOpenALError( alSourcePause( mOALSourceID ));
}

float rs::Sound::GetPlaybackTimeInSeconds() const {
	float playbackTime;
	rsCheckOpenALError( alGetSourcef( mOALSourceID, AL_SEC_OFFSET, &playbackTime ));
	return playbackTime;
}

int rs::Sound::GetPlaybackOffsetInSamples() const {
	int playbackOffsetSamples;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_SAMPLE_OFFSET, &playbackOffsetSamples ));
	return playbackOffsetSamples;
}

int rs::Sound::GetPlaybackOffsetInBytes() const {
	int playbackOffsetBytes;
	rsCheckOpenALError( alGetSourcei( mOALSourceID, AL_BYTE_OFFSET, &playbackOffsetBytes ));
	return playbackOffsetBytes;
}
