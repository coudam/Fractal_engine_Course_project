#include <chrono>
#include <iostream>
#include <utility>

class Time{
public:
	Time() = delete;;
	~Time() = delete;;

	template<
	 typename F, typename... Args>
	static decltype(auto) timer(F function, Args&&... args);

};