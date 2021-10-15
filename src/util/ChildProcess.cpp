#include <util/ChildProcess.h>
#include <util/CommandLine.h>

#ifdef _WIN32
	// MinGW-w64 headers don't define this,
	// and Boost.Winapi seems to use this symbol in certain places.
	//
	// Oh well - still ~700 lines less platform dependent code.
	#ifndef __kernel_entry
		#define __kernel_entry
	#endif
#endif

#include <boost/process/args.hpp>
#include <boost/process/async.hpp>
#include <boost/process/search_path.hpp>

namespace process = boost::process;

namespace collabvm::util {

	// helper literally banking on c++17 onwards RVO lmao
	template<class... Attrs>
	inline auto SpawnChild(Attrs&&... attrs) {
		return boost::process::child{std::forward<Attrs>(attrs)...};
	}

	process::child StartChildProcess(boost::asio::io_context& ioc, const std::string& commandline, OnExitHandler&& onexit) {
		auto split = SplitCommandLine(commandline);

		// TODO: probably should find some way to get mad if the split command line fails to work

		return StartChildProcess(ioc, split.value(), std::move(onexit));
	}

	process::child StartChildProcess(boost::asio::io_context& ioc, const std::vector<std::string>& args, OnExitHandler&& onexit) {
		if(args.size() < 2)		
			return SpawnChild(process::search_path(args[0]), process::on_exit = onexit, ioc);
		else {
			// there's probably a way to get a zero copy range of a container
			auto argsified = std::vector<std::string>{args.begin() + 1, args.end()};
			return SpawnChild(process::search_path(args[0]), process::args = argsified, process::on_exit = std::move(onexit), ioc);
		}
	}	

} // namespace collabvm::util