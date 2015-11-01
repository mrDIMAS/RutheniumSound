#include "Precompiled.h"

#include <windows.h>

void main() {
	try {
		rs::Log::Open( "rs.log" );

		rs::Engine engine;

		// Create 2D sound
		std::shared_ptr<rs::Buffer> buffer = std::make_shared<rs::Buffer>( "blast.ogg", false );
		rs::Sound sound2D( buffer );

		// Create 3D sound with auto-conversion buffer to mono
		std::shared_ptr<rs::Buffer> buffer3D = std::make_shared<rs::Buffer>( "blast.ogg", true );
		rs::Sound sound3D( buffer3D );

		// Create music with streaming buffer
		rs::Sound music( std::make_shared<rs::StreamingBuffer>( "lamp_buzz.ogg", true ));

		// Create first reverb effect
		std::shared_ptr<rs::EAXReverbEffect> reverbEffect1 = std::make_shared<rs::EAXReverbEffect>( );
		reverbEffect1->SetPreset( rs::EAXReverbEffect::Preset::Stonecorridor );

		// Create first effect slot for the first reverb effect
		std::shared_ptr<rs::EffectSlot> effectSlot1 = std::make_shared<rs::EffectSlot>( );
		effectSlot1->Attach( reverbEffect1 );

		// Create second reverb effect
		std::shared_ptr<rs::EAXReverbEffect> reverbEffect2 = std::make_shared<rs::EAXReverbEffect>( );
		reverbEffect2->SetPreset( rs::EAXReverbEffect::Preset::Hangar );

		// Create second effect slot for the second reverb effect
		std::shared_ptr<rs::EffectSlot> effectSlot2 = std::make_shared<rs::EffectSlot>( );
		effectSlot2->Attach( reverbEffect2 );

		// Attach music to first effect slot
		music.AttachToEffectSlot( effectSlot1 );
		music.Play();
		music.SetLooping( true );

		// Attach 3D sound to second effect slot
		sound3D.AttachToEffectSlot( effectSlot2 );

		while( !GetAsyncKeyState( VK_ESCAPE )) {
			if( GetAsyncKeyState( 'Q' )) {
				music.Pause();
			}
			if( GetAsyncKeyState( 'R' )) {
				music.Rewind();
			}
			if( GetAsyncKeyState( 'E' )) {
				if( !music.IsPlaying() ) {
					music.Play();
				}
			}
			if( GetAsyncKeyState( 'W' )) {
				if( !sound3D.IsPlaying() ) {
					sound3D.Play();
				}
			}
			music.DoStreaming();
		}
	} catch( std::runtime_error except ) {
		std::cout << except.what() << std::endl;
	}
}