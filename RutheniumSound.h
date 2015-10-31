#ifndef _RU_SOUND_H_
#define _RU_SOUND_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

namespace rs  {

////////////////////////////////////////////////////////////
/// \brief Simple 3D vector class 
////////////////////////////////////////////////////////////
struct Vec3 {
	float x;
	float y;
	float z;

	Vec3( float cX, float cY, float cZ ) : x( cX ), y( cY ), z( cZ ) { };
	Vec3( ) : x( 0.0f ), y( 0.0f ), z( 0.0f ) { };
};

////////////////////////////////////////////////////////////
/// \brief Base filter class 
////////////////////////////////////////////////////////////
class Filter {
protected:
	unsigned int mEFXFilterID;
public:
	explicit Filter();
	virtual ~Filter();
};

////////////////////////////////////////////////////////////
/// \brief Base effect class 
////////////////////////////////////////////////////////////
class Effect {
protected:
	unsigned int mEFXEffectID;
public:
	explicit Effect();
	virtual ~Effect();

	unsigned int GetEFXEffectID();
};

////////////////////////////////////////////////////////////
/// \brief EAX reverb effect class 
////////////////////////////////////////////////////////////
class EAXReverbEffect : public Effect {
public:
	enum class Preset : int {
		None = -1,
		//Generic
		Generic,
		Paddedcell,
		Room,
		Bathroom,
		Livingroom,
		Stoneroom,
		Auditorium,
		Concerthall,
		Cave,
		Arena,
		Hangar,
		Hallway,
		Stonecorridor,
		Alley,
		Forest,
		City,
		Mountains,
		Quarry,
		Plain,
		Parkinglot,
		Sewerpipe,
		Underwater,
		Drugged,
		Dizzy,
		Psychotic,

		//Castlepresets
		Castle_Smallroom,
		Castle_Shortpassage,
		Castle_Mediumroom,
		Castle_Longpassage,
		Castle_Largeroom,
		Castle_Hall,
		Castle_Cupboard,
		Castle_Courtyard,
		Castle_Alcove,

		//Factorypresets
		Factory_Alcove,
		Factory_Shortpassage,
		Factory_Mediumroom,
		Factory_Longpassage,
		Factory_Largeroom,
		Factory_Hall,
		Factory_Cupboard,
		Factory_Courtyard,
		Factory_Smallroom,

		//Icepalacepresets
		Icepalace_Alcove,
		Icepalace_Shortpassage,
		Icepalace_Mediumroom,
		Icepalace_Longpassage,
		Icepalace_Largeroom,
		Icepalace_Hall,
		Icepalace_Cupboard,
		Icepalace_Courtyard,
		Icepalace_Smallroom,

		//Spacestationpresets
		Spacestation_Alcove,
		Spacestation_Mediumroom,
		Spacestation_Shortpassage,
		Spacestation_Longpassage,
		Spacestation_Largeroom,
		Spacestation_Hall,
		Spacestation_Cupboard,
		Spacestation_Smallroom,

		//Woodengalleonpresets
		Wooden_Alcove,
		Wooden_Shortpassage,
		Wooden_Mediumroom,
		Wooden_Longpassage,
		Wooden_Largeroom,
		Wooden_Hall,
		Wooden_Cupboard,
		Wooden_Smallroom,
		Wooden_Courtyard,

		//Sportspresets
		Sport_Emptystadium,
		Sport_Squashcourt,
		Sport_Smallswimmingpool,
		Sport_Largeswimmingpool,
		Sport_Gymnasium,
		Sport_Fullstadium,
		Sport_Stadiumtannoy,

		//Prefabpresets
		Prefab_Workshop,
		Prefab_Schoolroom,
		Prefab_Practiseroom,
		Prefab_Outhouse,
		Prefab_Caravan,

		//Domeandpipepresets
		Dome_Tomb,
		Pipe_Small,
		Dome_Saintpauls,
		Pipe_Longthin,
		Pipe_Large,
		Pipe_Resonant,

		//Outdoorspresets
		Outdoors_Backyard,
		Outdoors_Rollingplains,
		Outdoors_Deepcanyon,
		Outdoors_Creek,
		Outdoors_Valley,

		//Moodpresets
		Mood_Heaven,
		Mood_Hell,
		Mood_Memory,

		//Drivingsimulationpresets
		Driving_Commentator,
		Driving_Pitgarage,
		Driving_Incar_Racer,
		Driving_Incar_Sports,
		Driving_Incar_Luxury,
		Driving_Fullgrandstand,
		Driving_Emptygrandstand,
		Driving_Tunnel,

		//Citypresets
		City_Streets,
		City_Subway,
		City_Museum,
		City_Library,
		City_Underpass,
		City_Abandoned,

		//Miscrooms
		Dustyroom,
		Chapel,
		Smallwaterroom,
	};
private:
	Preset mPreset;

public:
	explicit EAXReverbEffect();
	virtual ~EAXReverbEffect();

	void SetPreset( Preset preset );

	Preset GetPreset();
	float GetDensity() const;
	void SetDensity( float density );

	float GetDiffusion() const;
	void SetDiffusion( float diffusion );

	float GetGain() const;
	void SetGain( float gain );

	float GetHighFrequencyGain() const;
	void SetHighFrequencyGain( float hfGain );

	float GetLowFrequencyGain() const;
	void SetLowFrequencyGain( float lfGain );

	float GetDecayTime() const;
	void SetDecayTime( float decayTime );

	float GetDecayHighFrequencyRatio() const;
	void SetDecayHighFrequencyRatio( float hfRatio );

	float GetDecayLowFrequencyRatio() const;
	void SetDecayLowFrequencyRatio( float lfRatio );

	float GetReflectionsGain() const;
	void SetReflectionsGain( float reflectionsGain );

	float GetReflectionsDelay() const;
	void SetReflectionsDelay( float reflectionsDelay );

	rs::Vec3 GetReflectionsPan() const;
	void SetReflectionsPan( const rs::Vec3 & reflectionsPan );

	float GetLateReverbGain() const;
	void SetLateReverbGain( float lateReverbGain );

	float GetLateReverbDelay() const;
	void SetLateReverbDelay( float lateReverbDelay );

	rs::Vec3 GetLateReverbPan() const;
	void SetLateReverbPan( const rs::Vec3 & lateReverbPan );

	float GetEchoTime() const;
	void SetEchoTime( float echoTime );

	float GetEchoDepth() const;
	void SetEchoDepth( float echoDepth );

	float GetModulationTime() const;
	void SetModulationTime( float modulationTime );

	float GetModulationDepth() const;
	void SetModulationDepth( float modulationDepth );

	float GetAirAbsorptionHighFrequencyGain() const;
	void SetAirAbsorptionHighFrequencyGain( float hfGain );

	float GetHighFrequencyReference() const;
	void SetHighFrequencyReference( float hfReference );

	float GetLowFrequencyReference() const;
	void SetLowFrequencyReference( float lfReference );

	float GetRoomRolloffFactor() const;
	void SetRoomRolloffFactor( float roomRolloffFactor );

	float GetDecayHighFrequencyLimit() const;
	void SetDecayHighFrequencyLimit( float decayHFLimit );
};

////////////////////////////////////////////////////////////
/// \brief Base effect slot class 
////////////////////////////////////////////////////////////
class EffectSlot {
private:
	unsigned mEFXEffectSlotID;
	std::shared_ptr<Effect> mEffect;
public:
	explicit EffectSlot();
	virtual ~EffectSlot();
	void Attach( const std::shared_ptr<Effect> & effect );
	unsigned int GetEFXEffectSlotID();
};

////////////////////////////////////////////////////////////
/// \brief Simple string builder class 
////////////////////////////////////////////////////////////
class StringBuilder {
protected:
	std::stringstream mStream;
public:
	explicit StringBuilder( const char * str ) {
		std::stringstream::sync_with_stdio(false);
		mStream << str;
	}
	explicit StringBuilder(  ) {
		std::stringstream::sync_with_stdio(false);
	}
	template<class T>
	StringBuilder & operator<< (const T& arg) {
		mStream << arg;
		return *this;
	}
	operator std::string() const {
		return mStream.str();
	}
	const char * ToCStr() {
		return mStream.str().c_str();
	}
};

////////////////////////////////////////////////////////////
/// \brief Log class 
////////////////////////////////////////////////////////////
class Log {
public:
	static void Open( const std::string & file );
	static void Close();
	static void Write( const std::string & message );
};

////////////////////////////////////////////////////////////
/// \brief Engine class
////////////////////////////////////////////////////////////
class Engine {
private:
	void InitializeEAXEFXPresets();
public:
	enum class DistanceModel {
		None,
		InverseDistance,
		InverseDistanceClamped,
		LinearDistance,
		LinearDistanceClamped,
		ExponentDistance,
		ExponentDistanceClamped,
	};

	explicit Engine();
	virtual ~Engine();

	float GetSpeedOfSound() const;
	void SetSpeedOfSound( float speedOfSound );

	float GetDopplerFactor() const;
	void SetDopplerFactor( float dopplerFactor );

	void SetDistanceModel( DistanceModel distanceModel );
	DistanceModel GetDistanceModel() const;
};

////////////////////////////////////////////////////////////
/// \brief Decoder interface
////////////////////////////////////////////////////////////
class Decoder {
protected:
	char * mPCMData; ///< After each Decode() here placed a decoded data
	int mSize; ///< Size of decoded data
	int mFrequency; ///< Sampling frequency of decoded data
	int mFormat; ///< Format of decoded data (mono/stereo)
	int mFileFormat; ///< Format of encoded data (mono/stereo)
	int64_t mFullDecodedSize; ///< Size of PCM data of fully decoded file
	explicit Decoder();	
public:
	virtual ~Decoder();
	int GetFormat() const;
	int GetFrequency() const;
	int64_t GetFullDecodedSize() const;
	int GetSize() const;
	char * GetDecodedData() const;
	virtual void Decode( unsigned int blockSize, bool convertToMono ) = 0;
};

////////////////////////////////////////////////////////////
/// \brief Base buffer class 
////////////////////////////////////////////////////////////
class Buffer {
private:
	unsigned int mOALBufferID;
protected:
	std::string mFileName;
	bool mSupport3D;
	////////////////////////////////////////////////////////////
	/// \brief Special constructor for derived classes
	////////////////////////////////////////////////////////////
	explicit Buffer( const std::string & fileName, bool support3D, bool reserved );
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor 
	/// 
	/// If support3D is set to 'true', the data from file will be
	/// converted to mono. This is because stereo data can't be
	/// positioned in the world by sound source
	/// 
	/// \param support3D 'true' to enable support of 3D effects
	////////////////////////////////////////////////////////////
	explicit Buffer( const std::string & fileName, bool support3D );
	virtual ~Buffer( );

	std::string GetFileName() const;

	unsigned int GetOpenALBufferID();

	bool IsValid() const;

	int GetFrequency() const;
	int GetBitDepth() const;
	int GetChannelCount() const;
	int GetSizeInBytes() const;
};

class StreamingBuffer : public Buffer {
private:
	unsigned int mOALQueueBuffer[2];
	unsigned int mBlockSize;
	Decoder * mDecoder;
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor 
	/// 
	/// Streamed buffers is extremely useful to play large sounds
	/// (like music, or ambient).
	/// 
	/// If support3D is set to 'true', the data from file will be
	/// converted to mono. This is because stereo data can't be
	/// positioned in the world by sound source
	/// 
	/// \param support3D 'true' to enable support of 3D effects
	////////////////////////////////////////////////////////////
	explicit StreamingBuffer( const std::string & fileName, bool support3D, unsigned int blockSizeInBytes = 64536 );
	virtual ~StreamingBuffer( );

	////////////////////////////////////////////////////////////
	/// \brief Base sound source class 
	///
	/// destBufferNum = 0 - decoded data will be placed in mOALQueueBuffer[0]
	/// destBufferNum = 1 - decoded data will be placed in mOALQueueBuffer[1]
	///
	/// \param destBufferNum Destination buffer number
	///
	////////////////////////////////////////////////////////////
	void DecodeNextBlock( int destBufferNum );
	unsigned int * GetQueueBuffers();
};

////////////////////////////////////////////////////////////
/// \brief Base sound source class 
////////////////////////////////////////////////////////////
class Sound {
private:
	unsigned int mBufferNum;
	unsigned int mOALSourceID;
	std::shared_ptr<Buffer> mBuffer;
	std::shared_ptr<EffectSlot> mEffectSlot;
public:
	Sound();
	Sound( std::shared_ptr<Buffer> buffer );

	~Sound();

	void AttachToEffectSlot( const std::shared_ptr<EffectSlot> & effectSlot );
	void DetachFromEffectSlot();

	void DoStreaming();

	bool IsValid() const;

	float GetGain() const;
	void SetGain( float gain );

	float GetPitch() const;
	void SetPitch( float pitch );

	float GetMaxDistance() const;
	void SetMaxDistance( float maxDistance );
		
	float GetRolloffFactor() const;
	void SetRolloffFactor( float rolloffFactor );

	float GetReferenceDistance() const;
	void SetReferenceDistance( float referenceDistance );

	float GetMinGain() const;
	void SetMinGain( float minGain );

	float GetMaxGain() const;
	void SetMaxGain( float maxGain );

	float GetConeOuterGain() const;
	void SetConeOuterGain( float coneOuterGain );

	float GetConeInnerAngle() const;
	void SetConeInnerAngle( float coneInnerAngle );

	float GetConeOuterAngle() const;
	void SetConeOuterAngle( float coneOuterAngle );

	Vec3 GetPosition() const;
	void SetPosition( const Vec3 & position );

	Vec3 GetVelocity() const;
	void SetVelocity( const Vec3 & velocity );

	Vec3 GetDirection() const;
	void SetDirection( const Vec3 & direction );

	bool IsPositionRelativeToListener() const;
	void SetPositionRelativeToListener( bool relativePosition );

	bool IsStreaming() const;

	bool IsLooping() const;
	void SetLooping( bool looping );

	bool IsPlaying() const;
	void Play();

	bool IsStopped() const;
	void Stop();
	
	bool IsPaused() const;
	void Pause();

	float GetPlaybackTimeInSeconds() const;

	int GetPlaybackOffsetInSamples() const;

	int GetPlaybackOffsetInBytes() const;
};

////////////////////////////////////////////////////////////
/// \brief Base listener class
///
/// In whole engine there is only one listener, so all methods
/// are static
////////////////////////////////////////////////////////////
class Listener {
public:
	static float GetMasterGain();
	static void SetMasterGain( float masterGain );

	static rs::Vec3 GetPosition();
	static void SetPosition( const rs::Vec3 & position );

	static rs::Vec3 GetVelocity();
	static void SetVelocity( const rs::Vec3 & velocity );

	static rs::Vec3 GetOrientationUp();	
	static rs::Vec3 GetOrientationLook();
	static void SetOrientation( const rs::Vec3 & up, const rs::Vec3 & look );
};



};
#endif