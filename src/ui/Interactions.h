#pragma once
struct MouseInteractions
{
    bool clicked;
    double xpos;
    double ypos;

    double clickXpos;
    double clickYpos;

    void Reset()
    {
        clicked = false;
        clickXpos = 0.0;
        clickYpos = 0.0;

        xpos = 0.0;
        ypos = 0.0;
    }
};

struct Interactions
{
    MouseInteractions mouse;

    void Reset() {
        mouse.Reset();
    }
};