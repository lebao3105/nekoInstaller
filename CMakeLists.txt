cmake_minimum_required(VERSION 3.24)
project(nekoInstaller VERSION 0.1)

# Includes and dependencies
include(GNUInstallDirs)
include(FetchContent)

find_package(wxWidgets REQUIRED COMPONENTS net core base adv)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
	include(${wxWidgets_USE_FILE})
endif()

FetchContent_Declare(
	wxUI
	GIT_REPOSITORY https://github.com/rmpowell77/wxUI.git
	GIT_TAG main
)
FetchContent_MakeAvailable(wxUI)

set(ADD_FLUENTUI_ART ON)

FetchContent_Declare(
	wxMDArtProvider
	GIT_REPOSITORY https://github.com/lebao3105/wxMaterialDesignArtProvider.git
	GIT_TAG main
)
FetchContent_MakeAvailable(wxMDArtProvider)

# C++ Standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD LESS 20)
	set(CMAKE_CXX_STANDARD 20)
endif()

# Declare main target
add_executable(
	nekoInstaller
	
	MACOSX_BUNDLE

	src/installer.cpp
	src/main.cpp
	src/mainwindow.cpp
	src/settings.cpp
)

if(WIN32)
	target_sources(nekoInstaller PUBLIC src/win_only.rc)
	set_target_properties(nekoInstaller PROPERTIES WIN32_EXECUTABLE ON)
endif()

wxUI_SetupCompilerForTarget(nekoInstaller)
target_link_libraries(nekoInstaller ${wxWidgets_LIBRARIES} wxUI wxMDArtProvider)
