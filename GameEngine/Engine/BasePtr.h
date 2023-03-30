#pragma once

namespace Engine {
	struct RefCounters
	{
		unsigned long smartRefCount;
		unsigned long weakRefCount;

		RefCounters(unsigned long i_smartRefs, unsigned long i_weakRefs) :
			smartRefCount(i_smartRefs),
			weakRefCount(i_weakRefs)
		{}
	};

	template <class T>
	class BasePtr
	{
	public:
		//Default Constructor
		BasePtr() : 
			pPtr(nullptr),
			pRefCounters(nullptr)
		{}

		//Nullptr Constructor
		BasePtr(std::nullptr_t) :
			pPtr(nullptr),
			pRefCounters(nullptr)
		{}

		//Copy Constructor
		BasePtr(const BasePtr& i_other):
			pPtr(i_other.pPtr),
			pRefCounters(i_other.pRefCounters)
		{
			AddReference();
		}

		//Copy Constructor for derived class U
		template <class U>
		BasePtr(const BasePtr<U>& i_other) :
			pPtr(i_other.pPtr),
			pRefCounters(i_other.pRefCounters)
		{
			AddReference();
		}

		//Assignment operator
		BasePtr& operator=(const BasePtr& i_other) {
			if (this == &i_other)return *this;
			ReleaseReference();
			pPtr = i_other.pPtr;
			pRefCounters = i_other.pRefCounters;
			AddReference();
			return *this;
		}

		//Assignment operator for derived class U
		template <class U>
		BasePtr& operator=(const BasePtr<U>& i_other) {
			ReleaseReference();
			pPtr = i_other.pPtr;
			pRefCounters = i_other.pRefCounters;
			AddReference();
			return *this;
		}

		operator bool() const { return pPtr != nullptr; }
		bool operator==(BasePtr& i_other) const { return pPtr == i_other.pPtr; }
		bool operator!=(BasePtr& i_other) const { return pPtr != i_other.pPtr; }
		bool operator==(std::nullptr_t) const { return pPtr == nullptr; }
		bool operator!=(std::nullptr_t) const { return pPtr != nullptr; }

		~BasePtr() {
			ReleaseReference();
		}

		RefCounters* pRefCounters;

	protected:
		virtual void ReleaseReference() {}; //Returns whether the counter decreased to zero
		virtual void AddReference() {};//Add to the counter if it exists
		T* pPtr;
		
	};
}