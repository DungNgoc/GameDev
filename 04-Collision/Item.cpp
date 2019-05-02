#include "Item.h"
#include "Brick.h"


Ninja* Item::ninja = NULL;
Item::Item()
{
	srand(time(0));
	Random();
	switch (itemType)
	{
	case ITEM_SPIRIT_POINTS_BLU:
		this->width = 15;
		this->height = 15;
		break;
	case ITEM_SPIRIT_POINTS_RED:
		this->width = 15;
		this->height = 15;
		break;
	case ITEM_THROWING_STAR:
		this->width = 16;
		this->height = 16;
		break;
	case ITEM_WINDMILL_STAR:
		this->width = 16;
		this->height = 16;
		break;
	case ITEM_JUMP_AND_SLASH:
		this->width = 16;
		this->height = 16;
		break;
	case ITEM_FLAMES:
		this->width = 16;
		this->height = 16;
	case ITEM_FIRE_WHEEL:
		this->width = 16;
		this->height = 16;
	case ITEM_EXTRA_LIFE:
		this->width = 16;
		this->height = 16;
	case ITEM_BONUS_POINTS_BLUE:
		this->width = 17;
		this->height = 15;
	case ITEM_BONUS_POINT_RED:
		this->width = 16;
		this->height = 15;
		break;
	case ITEM_HEALTH_BLU:
		this->width = 12;
		this->height = 16;
		break;
	case ITEM_HEALTH_RED:
		this->width = 12;
		this->height = 16;
		break;
	case ITEM_EXTRA_TIME:
		this->width = 12;
		this->height = 15;
		break;
	default:
		break;
	}
	this->itemType = itemType;
}

Item::Item(int itemType)
{
	this->AddAnimation(9001);
	switch (itemType)
	{
	case ITEM_SPIRIT_POINTS_BLU:
		this->width = 15;
		this->height = 15;
		break;
	case ITEM_SPIRIT_POINTS_RED:
		this->width = 15;
		this->height = 15;
		break;
	case ITEM_THROWING_STAR:
		this->width = 16;
		this->height = 16;
		break;
	case ITEM_WINDMILL_STAR:
		this->width = 16;
		this->height = 16;
		break;
	case ITEM_JUMP_AND_SLASH:
		this->width = 16;
		this->height = 16;
		break;
	case ITEM_FLAMES:
		this->width = 16;
		this->height = 16;
	case ITEM_FIRE_WHEEL:
		this->width = 16;
		this->height = 16;
	case ITEM_EXTRA_LIFE:
		this->width = 16;
		this->height = 16;
	case ITEM_BONUS_POINTS_BLUE:
		this->width = 17;
		this->height = 15;
	case ITEM_BONUS_POINT_RED:
		this->width = 16;
		this->height = 15;
		break;
	case ITEM_HEALTH_BLU:
		this->width = 12;
		this->height = 16;
		break;
	case ITEM_HEALTH_RED:
		this->width = 12;
		this->height = 16;
		break;
	case ITEM_EXTRA_TIME:
		this->width = 12;
		this->height = 15;
		break;
	default:
		break;
	}
	this->itemType = itemType;
}


Item::~Item()
{
}

void Item::SetState(int state)
{
}



void Item::TakeSimonPointer(Ninja * ninja)
{
	Item::ninja = ninja;
}

void Item::Render(ViewPort *viewport)
{
	if (this->isEnable == true) {
		
		//animations[0]->Render(viewport, x, y);
		CSprites * sprites = CSprites::GetInstance();
		sprite = sprites->Get(itemType);
		sprite->Draw(viewport, x, y, 255);
	}
}

int Item::GetCurrentFrame()
{
	return anirender->getCurrentFrame();
}

void Item::Render()
{
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(itemType);
	sprite->Draw(x, y);
}

void Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 1;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//if (itemType != ITEM_MONEY)
		vy += NINJA_GRAVITY * dt;
	//vy = 0;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (this->isEnable == true)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}

	//reset untouchable timer if untouchable time has passed

	/*if (this->GetState() == ITEM_STATE_UP)
	{
		vy += -0.00100f;
		if (vy <= -0.118f)
			this->SetState(ITEM_STATE_IDLE);

	}*/


	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//block 
		// nx*0.4f : need to push out a bit to avoid overlapping next frame

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->ny < 0)
				{
					x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.4f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
			}

		}

	}
	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
}

void Item::Random()
{
	int percent = rand() % 100;

	if (percent < 90)
		RandomItem();
	else
		RandomWeapon();
}

void Item::RandomItem()
{
	int percent = rand() % 100;
	if (percent < 20)
	{
		itemType = ITEM_SPIRIT_POINTS_BLU;
	}
	else if (percent < 30)
	{
		itemType = ITEM_SPIRIT_POINTS_RED;
	}
	else if (percent < 40)
	{
		itemType = ITEM_BONUS_POINTS_BLUE;
	}
	else if (percent < 50)
	{
		itemType = ITEM_BONUS_POINT_RED;
	}
	else if (percent < 60)
	{
		itemType = ITEM_HEALTH_BLU;

	}
	else if (percent < 70)
	{
		itemType = ITEM_HEALTH_RED;
	}
	else if (percent < 90)
	{
		itemType = ITEM_EXTRA_TIME;
	}
	else if (percent < 100)
	{
		itemType = ITEM_EXTRA_LIFE;
	}
	
}

void Item::RandomWeapon()
{
	int percent = rand() % 100;
	
	if (percent < 25)
	{
		itemType = ITEM_THROWING_STAR;
	}
	else if (percent < 40)
	{
		itemType = ITEM_WINDMILL_STAR;
	}
	else if (percent < 55)
	{
		itemType = ITEM_FLAMES;
	}
	else if (percent < 65)
	{
		itemType = ITEM_FIRE_WHEEL;
	}
	else if (percent < 80)
	{
		itemType = ITEM_JUMP_AND_SLASH;
	}
	

}
