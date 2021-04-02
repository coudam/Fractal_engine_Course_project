#include <chrono>
#include <iostream>
#include <functional>

class Time{
public:
	Time() = delete;;
	~Time() = delete;;

	template<typename T, typename... Args>
	static void timer(std::string name, T f, Args&&... args){
		auto start = std::chrono::steady_clock::now();

		std::invoke(std::forward<T>(f), std::forward<Args>(args)...);

	    auto end = std::chrono::steady_clock::now();
	    std::chrono::duration<double> elapsed_seconds = end-start;
	    std::cout << "elapsed time of function \"" << name << "\" is : " << elapsed_seconds.count() << "s\n";	    
	}
};