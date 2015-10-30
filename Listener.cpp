#include "Precompiled.h"

float rs::Listener::GetMasterGain() {
	float masterGain;
	alGetListenerf( AL_GAIN, &masterGain );
	return masterGain;
}

void rs::Listener::SetMasterGain( float masterGain ) {
	alListenerf( AL_GAIN, masterGain );
}

rs::Vec3 rs::Listener::GetPosition() {
	rs::Vec3 position;
	alGetListener3f( AL_POSITION, &position.x, &position.y, &position.z );
	return position;
}

void rs::Listener::SetPosition( const rs::Vec3 & position ) {
	alListener3f( AL_POSITION, position.x, position.y, position.z );
}

rs::Vec3 rs::Listener::GetVelocity() {
	rs::Vec3 velocity;
	alGetListener3f( AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z );
	return velocity;
}

void rs::Listener::SetVelocity( const rs::Vec3 & velocity ) {
	alListener3f( AL_VELOCITY, velocity.x, velocity.y, velocity.z );
}

rs::Vec3 rs::Listener::GetOrientationUp() {
	float lookUpVectors[6];
	alGetListenerfv( AL_ORIENTATION, lookUpVectors );
	return rs::Vec3( lookUpVectors[3], lookUpVectors[4], lookUpVectors[5] );
}	

rs::Vec3 rs::Listener::GetOrientationLook() {
	float lookUpVectors[6];
	alGetListenerfv( AL_ORIENTATION, lookUpVectors );
	return rs::Vec3( lookUpVectors[0], lookUpVectors[1], lookUpVectors[2] );
}

void rs::Listener::SetOrientation( const rs::Vec3 & up, const rs::Vec3 & look ) {
	float lookUpVectors[6] = { look.x, look.y, look.z, up.x, up.y, up.z };
	alListenerfv( AL_ORIENTATION, lookUpVectors );
}