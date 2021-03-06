#pragma once

#include "BHive/BHivePCH.h"

namespace BHive
{ 

#define BIND_EVENT(x) [this](auto&&... args) -> decltype(auto){ return this->x(std::forward<decltype(args)>(args)...); }

	template<typename FunctionSigniture>
	struct BHive_API FEventDelegate
	{
		FEventDelegate(){};

		~FEventDelegate()
		{
			UnBindAll();
		}

		inline bool IsBound() { return BindedFunctions.size() > 0; }

		void AddBinding(const std::function<FunctionSigniture>& Function)
		{
			BindedFunctions.emplace_back(Function);
		}

		void RemoveBinding(const std::function<FunctionSigniture>& Function)
		{
			BindedFunctions.erase(Function);
		}

		void ExecuteIfBound()
		{
			if (IsBound())
			{
				Broadcast();
			}
		}

		void UnBindAll()
		{
			if (IsBound())
			{
				BindedFunctions.clear();
			}
		}

	protected:
		std::vector< std::function<FunctionSigniture>> BindedFunctions;
	};

	template<typename FunctionSigniture>
	struct FEventDelegateNoParams : public FEventDelegate<FunctionSigniture>
	{
		void Broadcast()
		{
			for (auto function : BindedFunctions)
			{
				function();
			}
		}
	};

	template<typename FunctionSigniture, typename Var1>
	struct FEventDelegateOneParam : public FEventDelegate<FunctionSigniture>
	{
		void Broadcast(Var1 Variable)
		{
			for (auto function : BindedFunctions)
			{
				function(Variable);
			}
		}
	};

	template<typename FunctionSigniture, typename Var1, typename Var2>
	struct FEventDelegateTwoParams : public FEventDelegate<FunctionSigniture>
	{
		void Broadcast(Var1 Variable1, Var2 Variable2)
		{
			for (auto function : BindedFunctions)
			{
				function(Variable1, Variable2);
			}
		}
	};

	template<typename FunctionSigniture, typename Var1, typename Var2, typename Var3>
	struct FEventDelegateThreeParams : public FEventDelegate<FunctionSigniture>
	{
		void Broadcast(Var1 Variable1, Var2 Variable2, Var3 Variable3)
		{
			for (auto function : BindedFunctions)
			{
				function(Variable1, Variable2, Variable3);
			}
		}
	};

	template<typename FunctionSigniture, typename Var1, typename Var2, typename Var3, typename Var4>
	struct FEventDelegateFourParams : public FEventDelegate<FunctionSigniture>
	{
		void Broadcast(Var1 Variable1, Var2 Variable2, Var3 Variable3, Var4 Variable4)
		{
			for (auto function : BindedFunctions)
			{
				function(Variable1, Variable2, Variable3, Variable4);
			}
		}
	};

	template<typename FunctionSigniture, typename Var1, typename Var2, typename Var3, typename Var4, typename Var5>
	struct FEventDelegateFiveParams : public FEventDelegate<FunctionSigniture>
	{
		void Broadcast(Var1 Variable1, Var2 Variable2, Var3 Variable3, Var4 Variable4, Var5 Variable5)
		{
			for (auto function : BindedFunctions)
			{
				function(Variable1, Variable2, Variable3, Variable4, Variable5);
			}
		}
	};

	template<typename FunctionSigniture, typename Var1, typename Var2,
		typename Var3, typename Var4, typename Var5, typename Var6>
	struct FEventDelegateSixParams : public FEventDelegate<FunctionSigniture>
	{
		void Broadcast(Var1 Variable1, Var2 Variable2, Var3 Variable3, Var4 Variable4, Var5 Variable5, Var6 Variable6)
		{
			for (auto function : BindedFunctions)
			{
				function(Variable1, Variable2, Variable3, Variable4, Variable5, Variable6);
			}
		}
	};

#define DECLARE_EVENT(EventName)\
	struct BHive_API F##EventName##Event : public FEventDelegateNoParams<void()>{};

#define DECLARE_ONE_PARAMETER_EVENT(EventName, type, parameter)\
	struct BHive_API F##EventName##Event : public FEventDelegateOneParam<void(type), type>{};

#define DECLARE_TWO_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2)\
	struct BHive_API F##EventName##Event : public FEventDelegateTwoParams<void(type1, type2), type1, type2>{};
	
#define DECLARE_THREE_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3)\
	struct BHive_API F##EventName##Event : public FEventDelegateThreeParams<void(type1, type2, type3)>{};

#define DECLARE_FOUR_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3, type4, paramater4)\
	struct BHive_API F##EventName##Event : public FEventDelegateFourParams<void(type1, type2, type3, type4), type1, type2, type3, type4>{};

#define DECLARE_FIVE_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3, type4, paramater4, type5, parameter5)\
	struct BHive_API F##EventName##Event : public FEventDelegateFiveParams<void(type1, type2, type3, type4, type5), type1, type2, type3, type4, type5>{};

#define DECLARE_SIX_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3, type4, paramater4, type5, parameter5, type6, parameter6)\
	struct BHive_API F##EventName##Event : public FEventDelegateSixParams<void(type1, type2, type3, type4, type5, type6), type1, type2, type3, type4, type5, type6>{};
}
