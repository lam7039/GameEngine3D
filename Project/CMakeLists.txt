cmake_minimum_required(VERSION 3.6)

project(GameEngine3D)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}_${VERSION_MINOR}_${VERSION_PATCH}")
message("Generating project files for GameEngine3D v" ${VERSION} " for " ${CMAKE_SYSTEM})

set(ROOT_DIR "${PROJECT_SOURCE_DIR}/../")

message("Configuring the environment")
include_directories(
	"${ROOT_DIR}/Include"
	"$ENV{PROGRAMFILES} (x86)/Microsoft DirectX SDK (June 2010)/Include"
)

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset configurations" FORCE)
	message("Configuration types: ${CMAKE_CONFIGURATION_TYPES}")
endif()

file(GLOB_RECURSE SOURCE_FILES ${ROOT_DIR}/Source/*.cpp)

file(GLOB_RECURSE HEADER_FILES ${ROOT_DIR}/Include/*.h)

add_library(GameEngine3D SHARED ${SOURCE_FILES} ${HEADER_FILES})

if(${WIN32})
	set(DEBUG_LINK_LIBRARIES 
		debug "${ROOT_DIR}Libraries/$<LOWER_CASE:$<CONFIG>>/d3d9.lib"
		debug "${ROOT_DIR}Libraries/$<LOWER_CASE:$<CONFIG>>/d3dx9.lib"
	)
	set(ALL_LINK_LIBRARIES ${DEBUG_LINK_LIBRARIES} ${RELEASE_LINK_LIBRARIES})
	target_link_libraries(GameEngine3D ${ALL_LINK_LIBRARIES})
endif()

add_custom_command(TARGET GameEngine3D POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "$<LOWER_CASE:$<CONFIG>>/GameEngine3D.lib" "${ROOT_DIR}/Libraries/$<LOWER_CASE:$<CONFIG>>/GameEngine3D.lib"
	COMMAND ${CMAKE_COMMAND} -E copy "$<LOWER_CASE:$<CONFIG>>/GameEngine3D.dll" "${ROOT_DIR}/Binaries/$<LOWER_CASE:$<CONFIG>>/GameEngine3D.dll"
)

