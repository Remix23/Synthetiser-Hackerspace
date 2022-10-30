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

    virtual void calcParams (double td);
    virtual double process (double sample); 

    bool isActive ();

    void activate();
    void deactivate();
};

