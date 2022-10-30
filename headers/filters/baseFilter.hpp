#pragma once

class BaseFilter
{
private:

    bool active = false;

public:

    BaseFilter();

    virtual void calcParams (double td);
    virtual double process (double sample); 

    bool isActive ();

    void activate();
    void deactivate();
    
};

