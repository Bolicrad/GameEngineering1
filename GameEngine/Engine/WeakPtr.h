#pragma once
#include "BasePtr.h"
namespace Engine{
	template <typename T>
	class WeakPtr : public BasePtr<T> {
	public:
		//Default Constructor
		WeakPtr() :BasePtr<T>() {}

		//Copy Constructor
		WeakPtr(const WeakPtr& i_other) : BasePtr<T>(i_other) {}

		//Copy Construct from Base (or SmartPtr)
		WeakPtr(const BasePtr& i_otherType) : BasePtr<T>(i_otherType){}

	protected:
		bool ReleaseReference() override {
			bool result = false;
			if (this->pRefCounters == nullptr)return result;
			this->pRefCounters->weakRefCount--;
			if ((this->pRefCounters->weakRefCount == 0) && (this->pRefCounters->smartRefCount == 0)) {
				delete this->pRefCounters;
				delete this->pPtr;
				result = true;
			}
			return result;
		}

		bool AddReference() override {
			if (this->pRefCounters == nullptr) return false;
			this->pRefCounters->weakRefCount++;
			return true;
		}
	};
}