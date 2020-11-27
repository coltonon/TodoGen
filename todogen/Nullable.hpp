#pragma once

template <typename T>
class Nullable {
public:
	bool isValid;
	T object;
	T operator()() {
		return this->object;
	}
	Nullable() : isValid(false) { }
	Nullable(bool valid) : isValid(valid) { }
	Nullable(T obj) : isValid(true), object(obj) { }

};