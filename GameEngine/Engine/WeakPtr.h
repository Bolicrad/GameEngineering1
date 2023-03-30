#pragma once
#include "BasePtr.h"
namespace Engine{
	template <class T>
	class WeakPtr : public BasePtr<T> {
	public:
		//Default Constructor
		WeakPtr() :BasePtr<T>() {}

		//Copy Constructor
		WeakPtr(const WeakPtr& i_other) : BasePtr<T>(i_other) {}

		//Copy Construct from Base (or SmartPtr)
		WeakPtr(const BasePtr<T>& i_otherType) : BasePtr<T>(i_otherType){}

		//Assignment operator for nullptr
		WeakPtr& operator=(std::nullptr_t) { ReleaseReference(); return *this; }

	protected:
		void ReleaseReference() override {
			if (this->pRefCounters == nullptr)return;
			this->pRefCounters->weakRefCount--;
			if ((this->pRefCounters->weakRefCount == 0) && (this->pRefCounters->smartRefCount == 0)) {
				delete this->pRefCounters;
				delete this->pPtr;
			}
			this->pPtr = nullptr;
			this->pRefCounters = nullptr;
		}

		void AddReference() override {
			if (this->pRefCounters == nullptr) return;
			this->pRefCounters->weakRefCount++;
		}
	};
}