#pragma once

#include <vector>
#include <graphics.h>
#include "misc/common.h"

// TODO: 更新图像是否要单拎出来
class Sprite
{
private:
    std::vector<IMAGE *> frames;
    int current_frame;
    float frame_rate;   // 帧切换的速率
    float frame_accum;  // 每次增加frame_rate的量，大于1时会切换到下一帧

protected:
    int x, y;

public:
    Sprite(int x, int y, float frame_rate);
    Sprite(int x, int y, float frame_rate, std::vector<IMAGE *> frames);
   
    // 添加图片帧
    void AddFrame(IMAGE *frame);

    // 更新图像并更新行为
    void Update();

    virtual void UpdateBehave() = 0;
};
