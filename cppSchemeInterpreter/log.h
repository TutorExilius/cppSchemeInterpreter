#ifndef LOG_H
#define LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

void init_log( const char *file );

#endif // LOG_H