#include "ev1527.h"
#define ContinueLogTimes 3

typedef enum
{
    evDecodeStart = 0,
    evDecodeData,
    evDecodeWait4Start,
    evDecodeCheckStart,
} __evDecodeState;

void ev1527Init(ev1527_core *core)
{
    // core->__state.decode = evDecodeWait4StartHigh;
    // core->__state.decode = evDecodeStart;
    core->__state.isStarted = 0;
    core->__state.dataLen = 0;
    core->keyState = keyState_NotPressed;
    core->learning = 0;
    core->__state.cnt4SameRcv = 0;
    core->__state.lastRcvData = 0;
    core->learnOk = 0;
    // core->hook->flash.load(&(core->registeredIDs), &(core->registeredLen));
}

// evU8_t evOK(ev1527_core *c)
// {
//     evU32_t us;
//     us = c->hook->timer.getUsTime();
//     if (us >= 500000)
//         return 1;
//     return 0;
// }

void evRaise(ev1527_core *c)
{
    evU32_t us;
    evU8_t signalRate;
    us = c->hook->timer.getUsTime();
    c->hook->timer.reset();

    if (!c->__state.isStarted)
    {

        if (c->__state.lastTimeStamp == 0)
            return;
        signalRate = us / c->__state.lastTimeStamp;
        if (signalRate < 25)
            return;
        if (signalRate > 36)
            return;
        c->__state.isStarted = 1;
        // us += c->__state.lastTimeStamp;
        c->__state.clkTime = 0;
        c->receiveData = 0;
        c->__state.dataLen = 0;
    }
    else // decode option high
    {
        c->receiveData <<= 1;
        if (us < c->__state.lastTimeStamp)
            ++c->receiveData;
        us += c->__state.lastTimeStamp;
        us >>= 2;
        c->__state.clkTime += us;
        ++c->__state.dataLen;
    }
}

evU8_t __checkId(ev1527_core *c)
{
    evU32_t id = c->receiveData;
    id >>= 4;
    return c->hook->flash.check(id);
}

// static inline void __addID(ev1527_core *c, evU32_t id)
// void __addID(ev1527_core *c)
// {
//     evU32_t id;
//     // c->hook->flash.load(&(c->registeredIDs), &(c->registeredLen));
// }

void evFall(ev1527_core *c)
{
    evU32_t us;
    us = c->hook->timer.getUsTime();
    c->hook->timer.reset();
    // if (c->__state.decode == evDecodeStart)
    // {
    //     c->__state.decode = evDecodeData;
    //     return;
    // }

    if (c->__state.dataLen == 23)
    {
        c->receiveData <<= 1;
        // if (us >= c->__state.dataHighTimeThreshold)
        if ((us * 12.0) > c->__state.clkTime)
            ++c->receiveData;
        c->__state.dataLen = 0;
        c->__state.isStarted = 0;
        c->__state.lastTimeStamp = 0;
        // if (__checkId(c))
        //     c->keyState = keyState_Short;
        // else if (c->learning)
        // {
        //     __addID(c);
        //     // c->keyState = keyState_Short;
        //     c->learning = 0;
        // }

        if (c->__state.lastRcvData == c->receiveData)
            ++(c->__state.cnt4SameRcv);
        else
            c->__state.cnt4SameRcv = 0;
        c->__state.lastRcvData = c->receiveData;

        if (c->__state.cnt4SameRcv < ContinueLogTimes)
            return;

        if (c->learning)
        {
            if (!__checkId(c))
            {
                evU32_t newId;
                newId = c->receiveData;
                newId >>= 4;
                c->hook->flash.dataAppend(newId);
                c->learnOk = 1;
            }
            // c->keyState = keyState_Short;
            c->learning = 0;
        }
        else if (__checkId(c))
            c->keyState = keyState_Short;
        return;
    }

    c->__state.lastTimeStamp = us;
}

// void evLoop(ev1527_core *c)
// {
// }
