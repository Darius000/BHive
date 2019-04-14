#pragma once

#include "Core.h"

namespace BHive
{
	class BHive_API Object
	{
	public:
		Object();
		virtual ~Object();

	private:
		std::string displayName;
		bool destroyed;

	public:

		std::string GetDisplayName();
		std::string GetClassDisplayName();

		void SetDisplayName(const std::string& string);
		void Destroy();
		bool IsDestroyed();

	protected:
		virtual void OnDestroyed();
	};

	template <class T>
	struct ErasePredicateShared
	{
		ErasePredicateShared(const T& inPointer)
			:Pointer(inPointer)
		{

		}

		const T& Pointer;

		bool operator()(const std::shared_ptr<T>& SharedPointer) const {
			return SharedPointer.get() == &Pointer;
		}
	};

	template <class T>
	struct ErasePredicateUnique
	{
		ErasePredicateUnique(const T& inPointer)
			:Pointer(inPointer)
		{

		}

		const T& Pointer;

		bool operator()(const std::unique_ptr<T>& UniquePointer) const {
			return UniquePointer.get() == &Pointer;
		}
	};
}