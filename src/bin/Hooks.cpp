#include "include/Hooks.h"
#include "include/guardCounter.h"
#pragma region MeleeHit
void Hook_MeleeHit::processHit(RE::Actor* victim, RE::HitData& hitData) {
	//hitDataProcessor::processHitData(hitData);
	
	using HITFLAG = RE::HitData::Flag;
	auto aggressor = hitData.aggressor.get().get();
	if (!victim || !aggressor || victim->IsDead()) {
		_ProcessHit(victim, hitData);
		return;
	}
	if (victim->IsPlayerRef() //player got hit
		&& (int)hitData.flags & (int)HITFLAG::kBlocked) { //player blocks hit
		guardCounter::GetSingleton()->registerBlock();
	}
	_ProcessHit(victim, hitData);
}

#pragma endregion

#pragma region MainUpdate
void Hook_MainUpdate::Update(RE::Main* a_this, float a2) {
	guardCounter::GetSingleton()->update();
	_Update(a_this, a2);
	
}
#pragma endregion