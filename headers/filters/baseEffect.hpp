#pragma once

class BaseEffect
{
private:
    bool active = false;
    bool debug = false;

public:
    BaseEffect();
    BaseEffect(bool active);
    BaseEffect(bool active, bool debug);

    virtual ~BaseEffect();

    virtual void calcParams(float td);
    virtual float process(float sample);

    bool isActive();

    void activate();
    void deactivate();
};
