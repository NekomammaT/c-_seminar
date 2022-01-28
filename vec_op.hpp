#ifndef INCLUDED_vec_op_hpp_

#define INCLUDED_vec_op_hpp_

#include <vector>


template <class T>
std::vector<T> operator+(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<T> ans = v1;
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] += v2[i];
	return ans;
}

template <class T>
std::vector<T> operator-(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<T> ans = v1;
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] -= v2[i];
	return ans;
}

template <class T>
std::vector<T>& operator+=(std::vector<T> &v1, const std::vector<T> &v2) {
	for (size_t i = 0, size = v1.size(); i < size; ++i)
		v1[i] += v2[i];
	return v1;
}

template <class T>
std::vector<T>& operator-=(std::vector<T> &v1, const std::vector<T> &v2) {
	for (size_t i = 0, size = v1.size(); i < size; ++i)
		v1[i] -= v2[i];
	return v1;
}

template <class T>
std::vector<T> operator*(const std::vector<T> &v, const T &c) {
	std::vector<T> ans = v;
	for (T &e : ans)
		e *= c;
	return ans;
}

template <class T>
std::vector<T> operator*(const T &c, const std::vector<T> &v) {
	std::vector<T> ans = v;
	for (T &e : ans)
		e *= c;
	return ans;
}

template <class T>
std::vector<T>& operator*=(std::vector<T> &v, const T &c) {
	for (T &e : v)
		e *= c;
	return v;
}

#endif
