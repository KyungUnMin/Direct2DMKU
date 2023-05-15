#include "PrecompileHeader.h"
#include "BossVursus.h"


void BossVursus::Update_FSM(float _DeltaTime)
{
	switch (CurState)
	{
	case BossVursus::State::Match:
		Update_Match();
		break;
	case BossVursus::State::CallName:

		break;
	case BossVursus::State::Fire:

		break;
	case BossVursus::State::Ready:

		break;
	}
}

void BossVursus::Update_Match()
{

}