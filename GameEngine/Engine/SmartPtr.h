#pragma once
#include "BasePtr.h"
namespace Engine {
	template <typename T>
	class SmartPtr : public BasePtr<T> {
	public:
		//Default Constructor
		SmartPtr() :BasePtr<T>() {}

		//Copy Constructor
		SmartPtr(const SmartPtr& i_other) : BasePtr<T>(i_other) {}

		//Construct from Instance of T
		SmartPtr(T* i_Ptr) :
			BasePtr<T>(),
			BasePtr<T>::pPtr(i_Ptr),
			BasePtr<T>::pRefCounters(new RefCounters(1, 0))
		{}

		//Copy Construct from Base (or WeakPtr)
		SmartPtr(const BasePtr& i_otherType) :
			BasePtr<T>(),
			BasePtr<T>::pPtr(i_otherType.pRefCounters->smartRefCount > 0 ? i_otherType.pPtr: nullptr),
			BasePtr<T>::pRefCounters(i_otherType.pRefCounters->smartRefCount > 0 ? i_otherType.pRefCounters : nullptr)
		{
			AddReference();
		}

		T& operator*() const { return *pPtr; }
		T* operator->() const { return pPtr; }

	protected:
		bool ReleaseReference() override {
			bool result = false;
			if (this->pRefCounters == nullptr)return result;
			this->pRefCounters->smartRefCount--;
			if (this->pRefCounters->smartRefCount == 0) {
				delete this->pPtr;
				result = true;
				if (this->pRefCounters->weakRefCount == 0) {
					delete this->pRefCounters;
				}
			}
			this->pPtr = nullptr;
			this->pRefCounters = nullptr;
			return result;
		}

		bool AddReference() override {
			if (this->pRefCounters == nullptr) return false;
			this->pRefCounters->smartRefCount++;
			return true;
		}
	};
}
