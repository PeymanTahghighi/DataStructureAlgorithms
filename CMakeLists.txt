#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)

project("DataStructureAlgorithms" CXX)

#----------------------------------------------------------------------------
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
set (EXECUTABLE_OUTPUT_PATH $(PROJECT_BINARY_DIR)/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
include_directories("include" "dep/include")
link_directories("dep/lib/SDL")
link_directories("dep/lib/SDL_TTF")
link_directories(${CMAKE_BINARY_DIR}/lib)
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
if(MSVC)
	add_definitions(/W4)
endif ()
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
set(TREE_HEADERS
	"include/Tree/Tree.h"
	"include/Prerequisities.h"
	"include/Tree/BST.h"
)

set(TREE_SOURCES
	"src/Tree/Tree.cpp"
	"src/Tree/BST.cpp"
)

add_library("Tree"
	${TREE_HEADERS}
	${TREE_SOURCES}
)

target_link_libraries("Tree" "SDL2")
target_link_libraries("Tree" "SDL2main")
target_link_libraries("Tree" "SDL2_ttf")

#----------------------------------------------------------------------------


#----------------------------------------------------------------------------
set("SIMPLE_TREE_TEST_SOURCES"
	"src/SimpleTreeTest/Main.cpp"
)
	
add_executable("SimpleTreeTest" 
		${SIMPLE_TREE_TEST_SOURCES}
)

target_link_libraries("SimpleTreeTest" "SDL2")
target_link_libraries("SimpleTreeTest" "SDL2main")
target_link_libraries("SimpleTreeTest" "SDL2_ttf")
target_link_libraries("SimpleTreeTest" "Tree.lib")
add_dependencies("SimpleTreeTest" "Tree")
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
set("SIMPLE_BST_TEST_SOURCES"
	"src/SimpleBSTTest/Main.cpp"
)

add_executable("SimpleBSTTest"
			${SIMPLE_BST_TEST_SOURCES}
)

target_link_libraries("SimpleBSTTest" "SDL2")
target_link_libraries("SimpleBSTTest" "SDL2main")
target_link_libraries("SimpleBSTTest" "SDL2_ttf")
target_link_libraries("SimpleBSTTest" "Tree.lib")
add_dependencies("SimpleBSTTest" "Tree")
#----------------------------------------------------------------------------

