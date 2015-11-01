#include "Precompiled.h"
#include "DecoderOGG.h"

rs::StreamingBuffer::StreamingBuffer( const std::string & fileName, bool support3D, unsigned int blockSizeInBytes ) :
	rs::Buffer( fileName, support3D, true ), mBlockSize( blockSizeInBytes ) {

	rsCheckOpenALError( alGenBuffers( 2, mOALQueueBuffer ));

	mDecoder = new DecoderOGG( fileName );

	for( int i = 0; i < 2; i++ ) {
		DecodeNextBlockToBuffer( mOALQueueBuffer[ i ] );
	}
}

rs::StreamingBuffer::~StreamingBuffer( ) {
	delete mDecoder;
	for( int i = 0; i < 2; i++ ) {
		if( alIsBuffer( mOALQueueBuffer[0] )) {
			alDeleteBuffers( 1, &mOALQueueBuffer[0] );
		}
	}
}

void rs::StreamingBuffer::Rewind() {
	mDecoder->SetEnabled( true );

	for( int i = 0; i < 2; i++ ) {
		DecodeNextBlockToBuffer( mOALQueueBuffer[ i ] );
	}
}

bool rs::StreamingBuffer::IsEndOfDataReached() {
	return !mDecoder->IsEnabled();
}

void rs::StreamingBuffer::DecodeNextBlockToBuffer( unsigned int destBuffer ) {
	if( mDecoder->IsEnabled() ) {
		mDecoder->Decode( mBlockSize, mSupport3D );
		rsCheckOpenALError( alBufferData( destBuffer, mDecoder->GetFormat(), mDecoder->GetDecodedData(), mDecoder->GetSize(), mDecoder->GetFrequency()));	
	}
}

unsigned int * rs::StreamingBuffer::GetQueueBuffers() {
	return mOALQueueBuffer;
}