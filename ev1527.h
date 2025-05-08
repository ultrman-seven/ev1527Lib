#ifndef F1BFFE6D_FCAF_499A_85E3_9E38968A15C5
#define F1BFFE6D_FCAF_499A_85E3_9E38968A15C5

// #include "stdint.h"
#include "evType.h"

typedef struct
{
    struct
    {
        void (*reset)();
        evU32_t (*getUsTime)();
    } timer;
    struct
    {
        void (*dataAppend)(evU32_t);
        evU8_t (*check)(evU32_t);
        // void (*load)(evU32_t **, evU32_t *);
    } flash;
} ev1527_Hooks;

typedef enum
{
    keyState_NotPressed = 0,
    keyState_Short,
    keyState_Long,
    keyState_DoubleClick
} ev1527_keyState;

typedef struct
{

#ifdef __C51__
    // struct
    // {
    //     evU8_t learning : 1;
    //     evU8_t keyState : 4;
    // };
    evU8_t learning : 1;
    evU8_t learnOk : 1;
    evU8_t keyState : 4;
    evU32_t receiveData;
#else
    // struct
    // {
    evU32_t learning : 1;
    evU32_t learnOk : 1;
    evU32_t keyState : 4;
    evU32_t receiveData : 24;
    // evU32_t receiveData;
    // evU32_t id : 20;
    // evU32_t keyVal : 4;
    // };
#endif

    struct
    {
        // evU32_t decode : 4;
        // evU32_t waitStart : 1;
        // evU32_t ready2RcvData : 1;
        // evU32_t dataHighTimeThreshold : 16;
#ifdef __C51__
        evU8_t isStarted : 1;
        evU8_t dataLen : 5;
        // evU16_t continuePressLog;
        evU16_t cnt4SameRcv;
        evU32_t lastRcvData;
#else
        evU32_t isStarted : 1;
        evU32_t dataLen : 5;
        evU32_t lastRcvData : 24;
        // evU32_t continuePressLog : 16;
        evU32_t cnt4SameRcv : 16;
#endif
        // evU32_t timeGap;
        evU32_t lastTimeStamp;
        // float clkTime;
        evU32_t clkTime;
    } __state;

    // evU32_t *registeredIDs;
    // evU32_t registeredLen;
    ev1527_Hooks *hook;
} ev1527_core;

void ev1527Init(ev1527_core *);
// void ev1527TriggerCallback(ev1527_core *);
void evRaise(ev1527_core *core);
void evFall(ev1527_core *core);
// void evLoop(ev1527_core *core);
// evU8_t evOK(ev1527_core *core);
#endif
