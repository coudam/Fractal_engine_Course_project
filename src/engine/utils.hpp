#pragma once
#include <vector>

template<typename T>
struct safe_vec_ptr{
	safe_vec_ptr() {}
	safe_vec_ptr(const safe_vec_ptr<T> &&t): it(t.it), id(t.id) {}
	safe_vec_ptr(const safe_vec_ptr<T> &t): it(t.it), id(t.id) {}
	safe_vec_ptr(std::vector<T> &v, int i): it(&v), id(i) {}
	
	T *operator ->() {return &((*it)[id]);}
	T& operator *() {return (*it)[id];}
	const T& operator =(const safe_vec_ptr<T> &t){it = t.it; id = t.id; return *this;}
	operator T() {return (*it)[id];}


	std::vector<T> *it;
	int id;
};
