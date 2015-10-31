#include "Precompiled.h"

#include <windows.h>

void main() {
	try {
		rs::Engine engine;

		std::shared_ptr<rs::Buffer> buffer = std::make_shared<rs::Buffer>( "blast.ogg", false );
		rs::Sound sound2D( buffer );

		std::shared_ptr<rs::Buffer> buffer3D = std::make_shared<rs::Buffer>( "blast.ogg", true );
		rs::Sound sound3D( buffer3D );

		rs::Sound music( std::make_shared<rs::StreamingBuffer>( "music.ogg", false ));

		music.Play();

		while( !GetAsyncKeyState( VK_ESCAPE )) {
			if( GetAsyncKeyState( 'Q' )) {
				music.Pause();
			}
			if( GetAsyncKeyState( 'E' )) {
				if( !music.IsPlaying() ) {
					music.Play();
				}
			}
			music.DoStreaming();
		}
	} catch( std::exception except ) {
		std::cout << except.what() << std::endl;
	}
}