#include"Character.h"

//Character::Character()
//{
//	valid = false;
//}


void TapGun::Character::Init()
{
	//Œ»İ‚Í•K—v‚È‚à‚Ì‚Ì‚İ‰Šú‰»‚µ‚Ä‚¢‚Ü‚·
	kind = CKIND_NONE;
	speed = 0.0f;
	valid = -1;
	frame = 0;
	pos = Vec3(0, 0, 0);
	target_pos = Vec3(0, 0, 0);
	speed_vec = Vec3(0, 0, 0);
}