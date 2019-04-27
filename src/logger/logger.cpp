// logger.cpp

// FIXME here is problem: auto flush not working

#include "logger.hpp"
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/value_ref.hpp>

namespace bl = boost::log;

using TextFile = boost::log::sinks::text_file_backend;
#ifndef NO_ASYNC_LOGGER
using TextSink = boost::log::sinks::asynchronous_sink<
    TextFile,
    boost::log::sinks::unbounded_ordering_queue<
        boost::log::attribute_value_ordering<unsigned int,
                                             std::less<unsigned int>>>>;
#else
using TextSink = boost::log::sinks::synchronous_sink<TextFile>;
#endif

static boost::shared_ptr<TextSink> fullSink_;
static boost::shared_ptr<TextSink> importantSink_;

UniqueLogger::UniqueLogger() {
  if (!fullSink_ && !importantSink_) {
    // clang-format off
    bl::formatter formatter =
                       bl::expressions::stream
                        << std::setw(4) << std::setfill('-')
                        << bl::expressions::attr<unsigned int>("LineID")
                        << std::setfill(' ')
                        << '[' << bl::expressions::format_date_time<bl::attributes::basic_time_traits::time_type>("TimeStamp", "%Y-%m-%d %H:%M:%S:%f") << ']'
                        << '[' << bl::expressions::attr<bl::attributes::current_thread_id::value_type>("ThreadID") << ']'
                        << '<' << bl::trivial::severity << '>' << "\t\t\t"
                        << std::setw(128) << std::left << bl::expressions::smessage 
                        << std::right << "\t\t\t"
                        << '(' << logger_value_file << ':' << logger_value_line << ' ' << logger_value_function << ')';
    // clang-format on

    fullSink_ = boost::make_shared<TextSink>(
        boost::make_shared<TextFile>(),
        bl::keywords::order =
            bl::make_attr_ordering("LineID", std::less<unsigned int>()));
    importantSink_ = boost::make_shared<TextSink>(
        boost::make_shared<TextFile>(),
        bl::keywords::order =
            bl::make_attr_ordering("LineID", std::less<unsigned int>()));

    auto [lockerFull, lockerImportant] = std::pair{
        fullSink_->locked_backend(), importantSink_->locked_backend()};

    lockerFull->set_file_name_pattern(LOGFILE_FULL);
    lockerFull->set_rotation_size(1024 * 1024);
    lockerFull->auto_flush(true);
    fullSink_->set_formatter(formatter);

    lockerImportant->set_file_name_pattern(LOGFILE_IMPORTANT);
    lockerImportant->set_rotation_size(1024 * 1024);
    lockerImportant->auto_flush(true);
    importantSink_->set_formatter(formatter);
    importantSink_->set_filter(boost::log::trivial::severity >
                               boost::log::trivial::info);

    bl::core::get()->add_sink(fullSink_);
    bl::core::get()->add_sink(importantSink_);

    bl::add_common_attributes();
  }
}

UniqueLogger::~UniqueLogger() {
  if (fullSink_ && importantSink_) {
#ifndef NO_ASYNC_LOGGER
    fullSink_->stop();
    importantSink_->stop();
#endif

    fullSink_->flush();
    fullSink_.reset();

    importantSink_->flush();
    importantSink_.reset();
  }
}
