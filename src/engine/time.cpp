#include "time.hpp"

template<typename F, typename... Args>
decltype(auto) Time::timer(F function, Args&&... args){

	auto start = std::chrono::steady_clock::now();

	auto ret = function(std::forward<Args>(args)...);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    return ret; 
}

