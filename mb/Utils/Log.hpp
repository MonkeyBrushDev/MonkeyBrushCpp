#ifndef __MB_LOG__
#define __MB_LOG__

#include <mb/api.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <chrono>
#include "StringUtils.hpp"

namespace mb
{
	class Log
	{
	private:
		Log(void) {}
		virtual ~Log() {}
	public:
		enum LogLevel {
			LOG_LEVEL_NONE = -1,		// no output
			LOG_LEVEL_ERROR = 2,		// only errors are output
			LOG_LEVEL_WARNING = 3,	// errors and warnings are output
			LOG_LEVEL_INFO = 4,			// errors, warnings, and informative messages
			LOG_LEVEL_DEBUG = 5,		// errors, warnings, informative messages and debug
			LOG_LEVEL_ALL = 99			// all messages are output
		};
		static int getLevel( void ) { return _level; }
		static void setLevel( int level ) { _level = level; }
	private:
		static int _level;
	public:
		template<typename ... Args>
    static void error( const std::string& msg, Args && ...args )
		{
			print(LogLevel::LOG_LEVEL_ERROR, "E", msg, std::forward< Args >(args)...);
		}
		template<typename ... Args>
    static void warning( const std::string& msg, Args && ...args )
		{
			print(LogLevel::LOG_LEVEL_WARNING, "W", msg, std::forward< Args >(args)...);
		}
		template<typename ... Args>
    static void info( const std::string& msg, Args && ...args )
		{
			print(LogLevel::LOG_LEVEL_INFO, "I", msg, std::forward< Args >(args)...);
		}
		template<typename ... Args>
    static void debug( const std::string& msg, Args && ...args )
		{
			print(LogLevel::LOG_LEVEL_DEBUG, "D", msg, std::forward< Args >(args)...);
		}
		template< typename ... Args >
    static void print( int level, const std::string& levelStr,
			std::string const &TAG, Args &&... args)
		{
			if (getLevel() >= level && _outputHandler != nullptr)
			{
				auto tp = std::chrono::system_clock::now();
				auto s = std::chrono::duration_cast< std::chrono::microseconds >(tp.time_since_epoch());
				auto t = (time_t)(s.count());

				auto str = StringUtils::toString(t, " ",
					levelStr, "/", TAG, " - ",
					std::forward< Args >(args)...);

        _outputHandler->print( str );
			}
		}

		public:
			class OutputHandler
			{
				public:
					virtual ~OutputHandler(void) { }
          virtual void print( const std::string& src ) = 0;
			};
			class ConsoleOutputHandler : public OutputHandler
			{
			public:
				ConsoleOutputHandler(void) { }
				virtual ~ConsoleOutputHandler(void) { }

        virtual void print( const std::string& src ) override;
			};
			class FileOutputHandler : public OutputHandler
			{
			public:
				FileOutputHandler(std::string const &path) 
          : _out(path, std::ios::out) { }
				virtual ~FileOutputHandler(void) { }

        virtual void print( const std::string& src ) override;
			private:
				std::ofstream _out;
			};
			class NullOutputHandler : public OutputHandler
			{
			public:
				NullOutputHandler(void) { }
				virtual ~NullOutputHandler(void) { }

        virtual void print( const std::string& ) override;
			};
			template< class T, typename ... Args >
			static void setOutputHandler(Args &&... args)
			{
				_outputHandler = std::move(
					std::unique_ptr< T >(new T(std::forward< Args >(args)...)));
			}
	private:
		static std::unique_ptr< OutputHandler > _outputHandler;
	};
}

#endif  /* __MB_LOG__ */
