#pragma once

#include <memory>

template<class T>
class Singleton
{
public:
	static T* GetInstance();
	static void Release();
private:
	static std::shared_ptr<T> mInstance;
};

template<class T>
std::shared_ptr<T> Singleton<T>::mInstance = nullptr;

template<class T>
inline T * Singleton<T>::GetInstance()
{
	if (!mInstance) {
		mInstance = std::make_shared<T>();
	}
	return mInstance.get();
}

template<class T>
inline void Singleton<T>::Release()
{
	if (mInstance) {
		mInstance.reset();
	}
	mInstance = nullptr;
}
