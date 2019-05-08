#include "Ninja.h"
#include "Item.h"
#include <algorithm>
#include "debug.h"
#include "Brick.h"
#include "Game.h"
#include "Enemy.h"
bool isHitting = false;


Ninja::Ninja()
{
	untouchable = 0;
	sword = new Sword();
	life =03;
	energy = 0;
	hp = 16;
	damage = 1;
	sword->SetDamage(damage);
}

void Ninja::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (!isTouchBrick|| isHurt)
		vy += NINJA_GRAVITY * dt;
	//vx = 0.1f;*/

	if (dy == 0)
	{
		isJump = false;
		isTouchBrick = true;
	}
	if (isHitting && state == NINJA_STATE_SIT)
	{
		sword->SetPosition(x, y, true);
		if (GetTickCount() - hitting_start > NINJA_HITTING_TIME)
		{
			hitting_start = 0;
			isHitting = false;
			reset(NINJA_SIT_HIT);
			sword->ResetAnimation();
			//reset()
			//etState(NINJA_STATE_IDLE);
		}

	}else
	if (isHitting)
	{
		if (nx>0)
			sword->isLeft = false;
		else sword->isLeft = true;
		sword->SetPosition(x, y, false);
		if (sword->GetCurrentFrame() == 2)
			sword->Update(dt, coObjects);
		if (GetTickCount() - hitting_start > NINJA_HITTING_TIME)
		{
			hitting_start = 0;
			isHitting = false;
			reset(NINJA_HIT_RIGHT);
			sword->ResetAnimation();
			//reset()
			//etState(NINJA_STATE_IDLE);
		}

	}
	

	if (GetTickCount() - untouchable_start > 2000)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (isHurt) {
		if (GetTickCount() - hurtable_start > 600)
		{
			hurtable_start = 0;
			hurtable = 0;
			isHurt = false;

		}
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	//if (state != MARIO_STATE_DIE)
	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CEnemy *>(coObjects->at(i)))
		{
			CEnemy *enemy = dynamic_cast<CEnemy *>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (untouchable == 0)
					{
						if (enemy->isEnable != false)
						{
							if (hp > 0)
							{
								hp -= enemy->GetDamage();
								StartUntouchable();
								SetState(NINJA_STATE_HURT);
								StartHurting();
							//	isTouchBrick = true;
							}
						}


					}
				}
			}

		}

	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		isTouchBrick = false;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 


		
			// Collision logic with Goombas
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				//isTouchBrick = true;
				
				if (dynamic_cast<Item *>(e->obj))
				{
					Item *item = dynamic_cast<Item *>(e->obj);
					if (item->isEnable == true) {
						switch (item->GetItemType())
						{
						case  ITEM_SPIRIT_POINTS_BLU:
							energy += 5;
							break;
						case  ITEM_SPIRIT_POINTS_RED:
							energy += 10;
							break;
						case ITEM_THROWING_STAR:

							break;
						case ITEM_WINDMILL_STAR:
							break;
						case ITEM_JUMP_AND_SLASH:

							break;
						case ITEM_FLAMES:

							break;
						case ITEM_FIRE_WHEEL:

							break;
						case ITEM_EXTRA_LIFE:

							break;
						case ITEM_BONUS_POINTS_BLUE:
							SetScore(GetScore() + 500);
							break;
						case ITEM_BONUS_POINT_RED:
							SetScore(GetScore() + 1000);
							break;
						case ITEM_HEALTH_BLU:

							break;
						case ITEM_HEALTH_RED:

							break;
						case ITEM_TIME_FREEZE:
							CEnemy::IsStop = true;
							CEnemy::StartTimeStop();
							break;
						default:
							//SetTypeOfWeapon(item->GetItemType());
							break;
						}

						item->isEnable = false;
						item->isDead = true;
					}


				}
				if (dynamic_cast<CBrick *>(e->obj))
				{
					if (e->ny < 0)
					{
						x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
						y += min_ty * dy + ny * 0.4f;
						if (!isHurt) {
							if (nx != 0) vx = 0;
							if (ny != 0) vy = 0;
						}
					}

				}
				else {
					x += dx;
					if (ny < 0)
						y += dy + ny * 0.3f;
					else if (ny > 0)
						y += dy + ny * -0.3f;
				}
				

			}
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++)
				delete coEvents[i];


		}
	
}
void Ninja::Render()
{
}
int Ninja::GetScore()
{
	return CEnemy::GetScore();
}
void Ninja::SetScore(int score) {
	CEnemy::SetScore(score);
}
void Ninja::Render(ViewPort *viewport)
{
	int ani = 0;
	if (nx > 0) {
		isLeft = true;
		sword->isLeft = true;
	}
	else
	{
		isLeft = false;
		sword->isLeft = false;
	}
	if (vx > 0)
		ani = NINJA_WALKING_RIGHT;
	else if (vx == 0)
	{
		if (state == NINJA_STATE_SIT)
			ani = NINJA_SIT_RIGHT;
		else ani = NINJA_IDLE_RIGHT;
		/*if (state == NINJA_STATE_SIT && isHitting)
		{
			ani = NINJA_SIT_HIT;
		}
		else if (state == NINJA_STATE_SIT)
			ani = NINJA_SIT_RIGHT;
		else 
			ani = NINJA_IDLE_RIGHT;*/
			
	}
	/*if (isHitting && vx == 0)
	{
		
		sword->Render(viewport);
		ani = NINJA_HIT_RIGHT;
	}*/
	if (isHitting && vx == 0)
	{
		if (state == NINJA_STATE_SIT)
		{
			sword->Render(viewport);
			ani = NINJA_SIT_HIT;
		}
		else {
			sword->Render(viewport);
			ani = NINJA_HIT_RIGHT;
		}
	}
	else if (isHitting && isJump) {
		ani = NINJA_HIT_RIGHT;
	}
	else if (isJump)
		ani = NINJA_ANI_JUMP;
	//else ani = NINJA_HIT_RIGHT;
	int alpha = 255;
	if (untouchable)   alpha = 200;
	animations[ani]->Render(viewport, x, y, alpha, isLeft);
	

	RenderBoundingBox(viewport);
}

void Ninja::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case NINJA_STATE_WALKING_RIGHT:
		vx = NINJA_WALKING_SPEED;
		nx = 1;
		break;

	case NINJA_STATE_IDLE:
		vx = 0;
		break;

	case NINJA_STATE_WALKING_LEFT:
		vx = -NINJA_WALKING_SPEED;
		nx = -1;
		break;
	case NINJA_STATE_JUMP:
		vy = -NINJA_JUMP_SPEED_Y;
		isJump = true;
		isTouchBrick = false;
		break;

	case NINJA_STATE_SIT:
		vx = 0;
		
		break;

	case NINJA_STATE_HURT:
	isTouchBrick = false;
		
		if (nx > 0)
		{
			vx = -0.1;
		}
		if (nx < 0)
		{
			vx = 0.1;
		}
		if (dy <= 0 || vy >= 0 || dy > 0)
			vy = -0.3;	

		break;
	}

}

void Ninja::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	bottom = y + 32;
	//if (isJump) 
	//bottom = y + 22;
	//
	//else 

		if (state == NINJA_STATE_IDLE || state == NINJA_STATE_SIT)
		{
			right = x + 17;


		}
		else {
			right = x + 20;
		}
}

void Ninja::SetTypeOfWeapon(int type)
{
	for (int i = 0; i < 3; i++)
	{
		switch (type)
		{

			/*case ITEM_HOLY_WATER:
				weapons[i] = holywater[i];
				currentWeapon = type;
				break;
			case ITEM_AXE:
				weapons[i] = axe[i];
				currentWeapon = type;
				break;
			case ITEM_DAGGER:
				weapons[i] = dagger[i];
				currentWeapon = type;
				break;
			case ITEM_BOOMERANG:
				weapons[i] = boomerang[i];
				currentWeapon = type;
				break;
			case ITEM_STOP_WATCH:
				weapons[i] = stopwatch[i];
				currentWeapon = type;
				break;*/
		default:
			break;
		}
	}
}




