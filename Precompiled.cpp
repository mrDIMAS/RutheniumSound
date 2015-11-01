#include "Precompiled.h"

static char errorDesc[4096];
void rsCheckOpenALErrorFunc( const char * file, int line, const char * func ) {	
	ALenum errorCode = alGetError();
	if( errorCode != AL_NO_ERROR ) {
		if( errorCode == AL_INVALID_NAME ) {
			sprintf_s( errorDesc, "OpenAL Error AL_INVALID_NAME occured in file %s in line %d in func %s", file, line, func );			
		} else if( errorCode == AL_INVALID_ENUM ) {
			sprintf_s( errorDesc, "OpenAL Error AL_INVALID_ENUM occured in file %s in line %d in func %s", file, line, func );			
		} else if( errorCode == AL_INVALID_VALUE ) {
			sprintf_s( errorDesc, "OpenAL Error AL_INVALID_VALUE occured in file %s in line %d in func %s", file, line, func );			
		} else if( errorCode == AL_INVALID_OPERATION ) {
			sprintf_s( errorDesc, "OpenAL Error AL_INVALID_OPERATION occured in file %s in line %d in func %s", file, line, func );			
		} else if( errorCode == AL_OUT_OF_MEMORY ) {
			sprintf_s( errorDesc, "OpenAL Error AL_OUT_OF_MEMORY occured in file %s in line %d in func %s", file, line, func );			
		} else {
			sprintf_s( errorDesc, "OpenAL Unknown Error occured in file %s in line %d in func %s", file, line, func );			
		}
		throw std::runtime_error( errorDesc );
	}
}