#pragma once
#include "BasePtr.h"
namespace Engine {
	template <class T>
	class SmartPtr : public BasePtr<T> {
	public:
		//Default Constructor
		SmartPtr() :BasePtr<T>() {}

		//Copy Constructor
		SmartPtr(const SmartPtr& i_other) : BasePtr<T>(i_other) {}

		//Construct from Instance of T
		SmartPtr(T* i_Ptr) 
		{
			this->pPtr = i_Ptr;
			if(i_Ptr!=nullptr)this->pRefCounters = new RefCounters(1, 0);
		}

		//Copy Construct from Base (or WeakPtr)
		SmartPtr(const BasePtr<T>& i_otherType):
			BasePtr<T>(i_otherType.pRefCounters->smartRefCount > 0 ? i_otherType : nullptr)
		{}

		//Assignment operator for nullptr
		SmartPtr& operator=(std::nullptr_t) { ReleaseReference(); return *this; }

		T& operator*() const { return *(this->pPtr); }
		T* operator->() const { return this->pPtr; }

	protected:
		void ReleaseReference() override {
			if (this->pRefCounters == nullptr) return;
			this->pRefCounters->smartRefCount--;
			if (this->pRefCounters->smartRefCount == 0) {
				delete this->pPtr;
				if (this->pRefCounters->weakRefCount == 0) {
					delete this->pRefCounters;
				}
			}
			this->pPtr = nullptr;
			this->pRefCounters = nullptr;
		}

		void AddReference() override {
			if (this->pRefCounters == nullptr) return;
			this->pRefCounters->smartRefCount++;
		}
	};
}
