#pragma once
#include "../sprite.h"

class Flame : public Sprite
{
    friend class FlameManager;

private:
    const float DURATION = 1;
    const float MIN_DROP_DURATION = 1;
    const float MAX_DROP_DURATION = 5;
    const int DROP_VELOCITY = 1;
    static const int PADDING_X = 1;
    static const int PADDING_Y = 1;
    static const int DELTA_X = 1;
    static const int DELTA_Y = 1;
    static constexpr float FRAME_RATE = 1;

    bool is_dropping;
    bool is_exist; // 指示火苗存在时间过久引起的消失问题
    float drop_duration;
    float current_exist_time;

public:
    Flame(int x, int y);
    Flame(int x, int y, std::vector<QPixmap *> frames);

    void UpdateBehave() override;

    ~Flame();
};
