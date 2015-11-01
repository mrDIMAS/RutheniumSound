#include "Precompiled.h"
#include "DecoderOGG.h"

rs::Buffer::Buffer( const std::string & fileName, bool support3D, bool reserved ) : 
	mFileName( fileName ), mSupport3D( support3D ), mOALBufferID( 0 ) {
	
}

rs::Buffer::Buffer( const std::string & fileName, bool support3D ) : 
	mSupport3D( support3D ), mFileName( fileName ), mOALBufferID( 0 ) {
	rsCheckOpenALError( alGenBuffers( 1, &mOALBufferID ));
	DecoderOGG oggDecoder( mFileName );
	oggDecoder.Decode( oggDecoder.GetFullDecodedSize(), mSupport3D );
	rsCheckOpenALError( alBufferData( mOALBufferID, oggDecoder.GetFormat(), oggDecoder.GetDecodedData(), oggDecoder.GetSize(), oggDecoder.GetFrequency()));
}

rs::Buffer::Buffer( const rs::Buffer & otherBuffer ) {

}

rs::Buffer::~Buffer( ) {
	
	if( IsValid() ) {
		rsCheckOpenALError( alDeleteBuffers( 1, &mOALBufferID ));
	}
}

std::string rs::Buffer::GetFileName() const {
	return mFileName;
}

unsigned int rs::Buffer::GetOpenALBufferID() {
	return mOALBufferID;
}

bool rs::Buffer::IsValid() const {
	return alIsBuffer( mOALBufferID ) != AL_FALSE;
}

int rs::Buffer::GetFrequency() const {
	int frequency;
	rsCheckOpenALError( alGetBufferi( mOALBufferID, AL_FREQUENCY, &frequency ));
	return frequency;
}

int rs::Buffer::GetBitDepth() const {
	int bitDepth;
	rsCheckOpenALError( alGetBufferi( mOALBufferID, AL_BITS, &bitDepth ));
	return bitDepth;
}

int rs::Buffer::GetChannelCount() const {
	int channelCount;
	rsCheckOpenALError( alGetBufferi( mOALBufferID, AL_CHANNELS, &channelCount ));
	return channelCount;
}

int rs::Buffer::GetSizeInBytes() const {
	int sizeBytes;
	rsCheckOpenALError( alGetBufferi( mOALBufferID, AL_SIZE, &sizeBytes ));
	return sizeBytes;
}