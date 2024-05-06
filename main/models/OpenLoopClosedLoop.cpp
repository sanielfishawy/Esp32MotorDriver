#include "OpenLoopClosedLoop.h"

bool OpenLoopClosedLoop::_closedLoop = true;

void OpenLoopClosedLoop::dangerousSetOpenLoop(){
    _closedLoop = false;
}

void OpenLoopClosedLoop::setClosedLoop(){
    _closedLoop = true;
}

bool OpenLoopClosedLoop::isOpenLoop(){
    return !_closedLoop;
}

bool OpenLoopClosedLoop::isClosedLoop(){
    return _closedLoop;
}