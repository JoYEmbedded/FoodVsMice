#include "sprite.h"

Sprite::Sprite(int x, int y, float frame_rate) : x(x), y(y), frame_rate(frame_rate)
{
    current_frame = 0;
    frame_accum = 0;
}

Sprite::Sprite(int x, int y, float frame_rate, std::vector<IMAGE *> frames) : 
    x(x), y(y), frame_rate(frame_rate), frames(frames) 
{
    current_frame = 0;
    frame_accum = 0;
};

void Sprite::AddFrame(IMAGE *frame)
{
    frames.push_back(frame);
}

void Sprite::Update()
{
    frame_accum += frame_rate;
    if (frame_accum >= 1)
    {
        current_frame = (current_frame + 1) % frames.size();
        frame_accum = 0;
    }
    UpdateBehave();
}
