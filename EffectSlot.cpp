#include "Precompiled.h"

rs::EffectSlot::EffectSlot() {
	if( alGenAuxiliaryEffectSlots ) {
		rsCheckOpenALError( alGenAuxiliaryEffectSlots( 1, &mEFXEffectSlotID ));
	}
}

rs::EffectSlot::~EffectSlot() {
	if( alDeleteAuxiliaryEffectSlots ) {
		rsCheckOpenALError( alDeleteAuxiliaryEffectSlots( 1, &mEFXEffectSlotID ));
	}
}

void rs::EffectSlot::Attach( const std::shared_ptr<rs::Effect> & effect ) {
	mEffect = effect;
	alAuxiliaryEffectSloti( mEFXEffectSlotID, AL_EFFECTSLOT_EFFECT, mEffect->GetEFXEffectID() );
}

unsigned int rs::EffectSlot::GetEFXEffectSlotID() {
	return mEFXEffectSlotID;
}