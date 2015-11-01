#include "Precompiled.h"
#include "DecoderOGG.h"


void rs::DecoderOGG::Decode( unsigned int blockSize, bool convertToMono ) {
	if( mEnabled ) {
		if( mPCMData ) {
			if( blockSize != mLastBlockSize ) {
				delete [] mPCMData;		
				mPCMData = new char[blockSize];
			}
		} else {
			mPCMData = new char[blockSize];
		}		

		// begin ogg decoding
		unsigned long totalBytesDecoded = 0;
		int currentSection = 0;

		// try to decode blockSize bytes
		while( totalBytesDecoded < blockSize ) {
			int bytesDecoded = ov_read( &mVorbisFile, (char*)( mPCMData + totalBytesDecoded ), blockSize - totalBytesDecoded, 0, 2, 1, &currentSection );

			// end of data
			if( bytesDecoded <= 0 ) {
				mEnabled = false;
				break;
			}

			totalBytesDecoded += bytesDecoded;
		}

		mSize = totalBytesDecoded;

		if( convertToMono ) {
			if( mFileFormat == AL_FORMAT_STEREO16 ) {
				mSize /= 2;
				short * sample16 = reinterpret_cast<short*>( mPCMData );	
				int countSamples = mSize / sizeof( short );
				for( int i = 0, k = 0; i < countSamples; i++, k += 2 ) {
					// cast each sample to 'int' need to avoid 'short' overflow
					int sample = ( static_cast<int>( sample16[k] ) + static_cast<int>( sample16[ k + 1 ] )) / 2;
					// clamp sample in [-32768;32767] to avoid 'clicks' in converted data
					if( sample > SHRT_MAX ) {
						sample = SHRT_MAX;
					}
					if( sample < SHRT_MIN ) {
						sample = SHRT_MIN;
					}
					sample16[i] = static_cast<short>( sample );
				}				
				mFormat = AL_FORMAT_MONO16;
			}
		}

		mLastBlockSize = blockSize;
	}
}

void rs::DecoderOGG::SetEnabled( bool state ) {
	mEnabled = state;
	// rewind
	if( mEnabled ) {
		ov_time_seek( &mVorbisFile, 0.0f );	
	}
}

rs::DecoderOGG::~DecoderOGG() {
	ov_clear( &mVorbisFile );
}

rs::DecoderOGG::DecoderOGG( const std::string & filename ) : mLastBlockSize( 0 ) {
	mSource.open( filename, std::ios_base::in | std::ios_base::binary );
	if( mSource.good() ) {
		ov_callbacks callbacks;
		callbacks.close_func = Close;
		callbacks.read_func = Read;
		callbacks.seek_func = Seek;
		callbacks.tell_func = Tell;
		if( ov_open_callbacks( &mSource, &mVorbisFile, nullptr, -1, callbacks ) >= 0 ) {
			vorbis_info * info = ov_info( &mVorbisFile, -1 );
			// size of fully decoded data can vary in wide limits, we assume it max possible (16-bit stereo)
			// of course this spent some additional memory for decoding, but it totally worth it
			// because if (for some reason) ov_pcm_total returns value less than actual size
			// this will cause engine to crash
			mFullDecodedSize = ov_pcm_total( &mVorbisFile, -1 ) * 4;				
			mFrequency = info->rate;
			if( info->channels == 2 ) {
				mFileFormat = AL_FORMAT_STEREO16;
				mFormat = mFileFormat;
			} else if( info->channels == 1 ) {
				mFileFormat = AL_FORMAT_MONO16;
				mFormat = mFileFormat;
			} else {
				ov_clear( &mVorbisFile );
				throw std::runtime_error( "This file is unsupported - channel count > 2!" );
			}
		} else {
			throw std::runtime_error( "This file is not valid ogg!" );
		}
	} else {
		throw std::runtime_error( "Unable to read file!" );
	}
}

int rs::DecoderOGG::Close( void *datasource ) {
	(void)datasource;
	return 0;
}

long rs::DecoderOGG::Tell( void *datasource ) {
	std::istream * file = reinterpret_cast<std::istream*>(datasource);
	return static_cast<size_t>( file->tellg() );
}

int rs::DecoderOGG::Seek( void * datasource, ogg_int64_t offset, int whence ) {
	std::istream * file = reinterpret_cast<std::istream*>( datasource );
	std::ios_base::seekdir dir;
	file->clear();
	switch( whence ) {
	case SEEK_SET: 
		dir = std::ios::beg;  
		break;
	case SEEK_CUR: 
		dir = std::ios::cur;  
		break;
	case SEEK_END: 
		dir = std::ios::end;  
		break;
	default: 
		return -1;
	}
	file->seekg( (std::streamoff)offset, dir );
	return ( file->fail() ? -1 : 0 );
}

size_t rs::DecoderOGG::Read( void * ptr, size_t size, size_t nmemb, void * datasource ) {
	std::istream * file = reinterpret_cast<std::istream*>( datasource );
	file->read((char*)ptr, size * nmemb);
	return static_cast<size_t>( file->gcount() );
}
