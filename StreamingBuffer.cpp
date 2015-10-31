#include "Precompiled.h"
#include "DecoderOGG.h"

rs::StreamingBuffer::StreamingBuffer( const std::string & fileName, bool support3D, unsigned int blockSizeInBytes ) :
	rs::Buffer( fileName, support3D, true ), mBlockSize( blockSizeInBytes ) {

	rsCheckOpenALError( alGenBuffers( 2, mOALQueueBuffer ));

	mDecoder = new DecoderOGG( fileName );

	for( int i = 0; i < 2; i++ ) {
		DecodeNextBlock( i );
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

void rs::StreamingBuffer::DecodeNextBlock( int destBufferNum ) {
	if( destBufferNum < 0 && destBufferNum > 1 ) {
		throw std::exception( "Unable to decode! Invalid buffer number" );
	} else {
		mDecoder->Decode( mBlockSize, mSupport3D );
		rsCheckOpenALError( alBufferData( mOALQueueBuffer[destBufferNum], mDecoder->GetFormat(), mDecoder->GetDecodedData(), mDecoder->GetSize(), mDecoder->GetFrequency()));
	}
}

unsigned int * rs::StreamingBuffer::GetQueueBuffers() {
	return mOALQueueBuffer;
}