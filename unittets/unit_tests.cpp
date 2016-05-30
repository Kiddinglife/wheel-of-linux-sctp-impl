#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "globals.h"

TEST(test_case_logging, test_read_trace_levels)
{
    read_trace_levels();
}

#include "gecotimer.h"
static bool action(timer_id_t& id, void*, void*)
{
    EVENTLOG(VERBOSE, "timer triggered\n");
    return NOT_RESET_TIMER_FROM_CB;
}
TEST(test_case_timer_mgr, test_timer_mgr)
{
    timer_mgr tm;
    timer_id_t ret1 = tm.add_timer(TIMER_TYPE_INIT, 1000, action);
    timer_id_t ret2 = tm.add_timer(TIMER_TYPE_SACK, 1, action);
    timer_id_t ret3 = tm.add_timer(TIMER_TYPE_SACK, 15, action);
    tm.print(VERBOSE);
    tm.delete_timer(ret1);
    tm.delete_timer(ret2);
    tm.print(VERBOSE);
}

#include "auth.h"
TEST(test_case_auth, test_md5_1)
{
    const char* testdata = "202cb962ac59075b964b07152d234b70";
    const char* result = "d9b1d7db4cd6e70935368a1efb10e377";
    MD5 md5_0(testdata);
    EVENTLOG1(VERBOSE, "DGEST %s", md5_0.hexdigest().c_str());
    EXPECT_STREQ(md5_0.hexdigest().c_str(), result);

    testdata = "d9b1d7db4cd6e70935368a1efb10e377";
    result = "7363a0d0604902af7b70b271a0b96480";
    MD5 md5_1(testdata);
    EXPECT_STREQ(md5_1.hexdigest().c_str(), result);
    EVENTLOG1(VERBOSE, "DGEST %s", md5_1.hexdigest().c_str());
    int a = 123;
    MD5 md5_2((const char*)&a);
}

#include "geco-ds-malloc.h"
using namespace geco::ds;
TEST(test_case_malloc, test_alloc_dealloc)
{
    int times = 0;
    for (int j = 0; j <= 5120; j++)
    {
        times++;
        char* intptr = (char*)single_client_alloc::allocate(j);
        int mod = 0;
        int i;
        if (intptr != NULL)
            memset(intptr, 0, j); //3000ms
        single_client_alloc::deallocate(intptr, j);
        if (j >= 5120) j = 0;
        if (times >= 1000000) break;
    }
    single_client_alloc::destroy();
}

TEST(test_case_hash, test_sockaddr2hashcode)
{
    sockaddrunion localsu;
    str2saddr(&localsu, "192.168.1.107", 36000);
    sockaddrunion peersu;
    str2saddr(&peersu, "192.168.1.107", 36000);
    EVENTLOG1(VERBOSE, "hash(addr pair { localsu: 192.168.1.107:36000 peersu: 192.168.1.107:36000 }) = %u", sockaddr2hashcode(&localsu, &peersu));

    str2saddr(&localsu, "192.168.1.107", 36001);
    str2saddr(&peersu, "192.168.1.107", 36000);
    EVENTLOG1(VERBOSE, "hash(addr pair { localsu: 192.168.1.107:36001 peersu: 192.168.1.107:36000 }) = %u", sockaddr2hashcode(&localsu, &peersu));
}