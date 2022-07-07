#include "egg.h"

const int COOL_DOWN_TIME = 1;
const int HEALTH = 100;
const int DELTA_X = 15;
const int DELTA_Y = 35;
const float FRAME_RATE = 1;

// projectile
const int PROJECTILE_DELTA_X = 1;
const int PROJECTILE_DELTA_Y = 1;
const int PROJECTILE_START = 26;
const int PROJECTILE_VELOCITY_Y = 10;
const int PROJECTILE_DAMAGE = 20;


bool Egg::Func()
{
    std::vector<QPixmap *> imgs(frames.begin() + PROJECTILE_START, frames.end());
    Mouse *target = mouse_manager->GetLeftestMouse(draw_item.x, row);
    if (target != nullptr)
    {
        projectile = new PitchProjectile(draw_item.x, draw_item.y, PROJECTILE_DELTA_X, PROJECTILE_DELTA_Y,
                                         FRAME_RATE, imgs, PROJECTILE_VELOCITY_Y, PROJECTILE_DAMAGE, target);
        projectile_manager->AddProjectile(projectile);
        return true;

    }
    return false;
}

Egg::Egg(int x, int y, int row, std::vector<QPixmap *> frames, MouseManager *mouse_manager, ProjectileManager *projectile_manager)
    : Food(x, y, DELTA_X, DELTA_Y, row, frames, HEALTH, COOL_DOWN_TIME), mouse_manager(mouse_manager), projectile_manager(projectile_manager) {}
