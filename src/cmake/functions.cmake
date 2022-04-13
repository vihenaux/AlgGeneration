# Macro to add warning flags

macro(ADD_COMPILER_FLAG FLAG_TO_ADD)
	if(${ARGC} GREATER 1)
		message(FATAL_ERROR "Too much arguments. \"${FLAG_TO_ADD}\" and \"${ARGN}\" not applied.")
	else()
		string(FIND ${FLAG_TO_ADD} " " out)
		if(${out} GREATER_EQUAL 0)
			message(WARNING "Several options in \"${FLAG_TO_ADD}\". Would be prettier with only one.")
		endif()
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG_TO_ADD}")
	endif()
endmacro()