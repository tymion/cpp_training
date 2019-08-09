#pragma once

#ifdef DEBUG
#include <stdio.h>

#define LOG printf

#define ASSERT_PTR(ptr) \
            if (ptr == nullptr) { \
                LOG("ASSERT!!! In file:%s:%d\n", __FILE__, __LINE__); \
                abort(); \
            }
#else

#define LOG(...)

#define ASSERT_PTR(...)

#endif

/*
#define BOOST_LOG(arg) \
if (rec) \
{ \
    logging::record_ostream strm(rec);\
    strm << arg; \
    strm.flush(); \
    lg.push_record(boost::move(rec)); \
}
*/
