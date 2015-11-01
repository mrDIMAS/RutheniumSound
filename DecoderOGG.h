#ifndef _DECODER_OGG_H_
#define _DECODER_OGG_H_

#include "ogg/ogg.h"
#include "vorbis/vorbisfile.h"

namespace rs {

class DecoderOGG : public rs::Decoder {
private:
	static size_t Read( void * ptr, size_t size, size_t nmemb, void * datasource );
	static int Seek( void * datasource, ogg_int64_t offset, int whence );
	static long Tell( void *datasource );
	static int Close( void *datasource );

	unsigned int mLastBlockSize;
	std::ifstream mSource;
	OggVorbis_File mVorbisFile;
public:
	explicit DecoderOGG( const std::string & filename );
	virtual ~DecoderOGG();
	virtual void Decode( unsigned int blockSize, bool convertToMono ) final;
	virtual void SetEnabled( bool state ) final;
};

};

#endif