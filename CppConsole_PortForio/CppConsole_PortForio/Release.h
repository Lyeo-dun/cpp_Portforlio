#pragma once
template <typename T>
void Safe_Release(T& _obj) {
	if (_obj != nullptr)
	{
		delete _obj;
		_obj = nullptr;
	}
}

#define SAFE_RELEASE(_obj) Safe_Release(_obj)