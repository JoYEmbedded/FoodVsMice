#include "sprite/sun.h"
#include "misc/random.h"
#include "time_manager.h"
#include "game_manager.h"


Sun::Sun(int x, int y)
{
    is_exist = true;
    this->x = x;
    this->y = y;
    is_dropping = true;
    current_exist_time = 0;
    drop_duration = Random::RandFloat(MIN_DROP_DURATION, MAX_DROP_DURATION);
}

void Sun::UpdateBehave()
{
    current_exist_time += TimeManager::DELTA_TIME;
    
    if (current_exist_time > DURATION) // 阳光一段时间后会消失
    {
        is_exist = false;
        return;
    }
    else if (is_dropping) // 坠落
    {
        y += DROP_VELOCITY * TimeManager::DELTA_TIME;

        if (current_exist_time >= drop_duration)
        {
            is_dropping = false;
        }
    }
}

Sun::~Sun()
{
    // TODO: 擦除图片
}