#include "Precompiled.h"

rs::Decoder::Decoder() : 
	mFormat( AL_FORMAT_MONO16 ), mFrequency( 0 ), mPCMData( nullptr ), mSize( 0 ), mFullDecodedSize( 0 ),
	mFileFormat( AL_FORMAT_MONO16 ), mEnabled( true ) {

}

rs::Decoder::~Decoder() {
	if( mPCMData ) {
		delete [] mPCMData;
	}
}

bool rs::Decoder::IsEnabled() {
	return mEnabled;
}

int rs::Decoder::GetFormat() const {
	return mFormat;
}

int rs::Decoder::GetFrequency() const {
	return mFrequency;
}

int64_t rs::Decoder::GetFullDecodedSize() const {
	return mFullDecodedSize;
}

int rs::Decoder::GetSize() const {
	return mSize;
}

char * rs::Decoder::GetDecodedData() const {
	return mPCMData;
}