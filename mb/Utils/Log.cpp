#include "Log.hpp"

#include "MemoryUtils.hpp"

namespace mb
{
	std::unique_ptr< Log::OutputHandler > Log::_outputHandler =
		make_unique< Log::ConsoleOutputHandler>();
	int Log::_level = Log::LogLevel::LOG_LEVEL_INFO;
}
