
include "delay.h"
#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif
void QTest::qSleep(int ms)
{
    QTEST_ASSERT(ms > 0);

#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };

#endif
}
