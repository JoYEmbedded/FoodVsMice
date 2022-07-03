#pragma once
#include "../sprite.h"

class Projectile : public Sprite
{
public:
    Projectile(int x, int y, float frame_rate, std::vector<QPixmap *> frames, int velocity, int damage);

    virtual void UpdateBehave() = 0;

protected:
    int velocity;
    int damage;
};
