/*


*/



#pragma once



#include "LAL_Cpp_STL.hpp"
#include "LAL_BasicTypes.hpp"



namespace LAL
{
	template<typename Type>
	using DynamicArray = std::vector<Type>;

	template<typename Type>
	using Queue = std::queue<Type>;

	template<typename Type, DataSize NumberOfElements>
	using StaticArray = std::array<Type, NumberOfElements>;
}