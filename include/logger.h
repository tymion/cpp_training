#pragma once

#define BOOST_LOG(arg) \
if (rec) \
{ \
    logging::record_ostream strm(rec);\
    strm << arg; \
    strm.flush(); \
    lg.push_record(boost::move(rec)); \
}
