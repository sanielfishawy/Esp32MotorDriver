#pragma once

#ifdef __cplusplus

class OpenLoopClosedLoop{

    public:
        static void dangerousSetOpenLoop();
        static void setClosedLoop();
        static bool isOpenLoop();
        static bool isClosedLoop();

    private:
        static bool _closedLoop;
};
#endif // __cplusplus