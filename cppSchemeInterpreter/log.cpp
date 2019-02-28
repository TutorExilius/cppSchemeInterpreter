#include "log.h"

void init_log( const char *file )
{
	auto file_logger = spdlog::basic_logger_mt( "fLog", file );
	spdlog::set_default_logger( file_logger );

	spdlog::set_pattern( "[%Y-%m-%dT%H:%M:%S.%e%z] %v" );
}