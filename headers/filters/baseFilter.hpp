#pragma once

class BaseFilter
{
private:

    bool active = false;

public:

    BaseFilter();

    virtual void calcParams (double td);
    virtual void process (double buff[]); 

    bool isActive ();

    void activate();
    void deactivate();
    
};

