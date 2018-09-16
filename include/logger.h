#ifndef __LOGGER_H__
#define __LOGGER_H__

#define BOOST_LOG(arg) \
if (rec) \
{ \
    logging::record_ostream strm(rec);\
    strm << arg; \
    strm.flush(); \
    lg.push_record(boost::move(rec)); \
}

#endif /* __LOGGER_H_ */
