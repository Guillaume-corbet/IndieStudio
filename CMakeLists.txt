cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(SRCS
    src/main.cpp
    src/Game.cpp
    src/Load.cpp
    src/Player.cpp
    src/Bot.cpp
    src/Menu.cpp
    src/EventReceiver.cpp
    src/Graphique.cpp
    src/Bomb.cpp
    src/Item.cpp
    src/Display.cpp
    src/Save.cpp
    )

set(HEADERS
    include/my.h
    include/Game.hpp
    include/Load.hpp
    include/Player.hpp
    include/Bot.hpp
    include/ICharacter.hpp
    include/Menu.hpp
    include/EventReceiver.hpp
    include/Graphique.hpp
    include/Bomb.hpp
    include/Item.hpp
    include/Display.hpp
    include/Save.hpp
    )

add_executable(bomberman ${SRCS} ${HEADERS})

IF (NOT Irrlicht_FOUND)
  FIND_PATH(Irrlicht_INCLUDE_DIRS REQUIRED
    NAMES
      irrlicht.h
    PATHS
    /usr/include/irrlicht/        # Default Fedora28 system include path
    /usr/local/include/irrlicht/  # Default Fedora28 local include path
    ${CMAKE_MODULE_PATH}/include/ # Expected to contain the path to this file for Windows10
    ${Irrlicht_DIR}/include/      # Irrlicht root directory (if provided)
  )

  IF (MSVC)     # Windows
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  ELSE (MSVC)   # Linux
    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
  ENDIF(MSVC)

  FIND_LIBRARY(Irrlicht_LIBRARIES REQUIRED
    NAMES
      Irrlicht
    PATHS
      /usr/lib64/                   # Default Fedora28 library path
      /usr/lib/                     # Some more Linux library path
      /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
      /usr/local/lib/               # Some more Linux library path
      /usr/local/lib64/             # Some more Linux library path
      ${CMAKE_MODULE_PATH}/         # Expected to contain the path to this file for Windows10
      ${Irrlicht_DIR}/              # Irrlicht root directory (if provided)
  )
ENDIF (NOT Irrlicht_FOUND)

IF (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)
  SET(Irrlicht_FOUND TRUE)
ELSE (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)
  SET(Irrlicht_FOUND FALSE)
ENDIF (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)

IF (Irrlicht_FIND_REQUIRED AND NOT Irrlicht_FOUND)
  MESSAGE(FATAL_ERROR
    "  Irrlicht not found.\n"
    "      Windows: Fill CMake variable CMAKE_MODULE_PATH to the provided directory.\n"
    "      Linux: Install Irrlicht using your package manager ($> sudo dnf install irrlicht-devel).\n"
  )
ENDIF (Irrlicht_FIND_REQUIRED AND NOT Irrlicht_FOUND)

IF (Irrlicht_FOUND)
  target_include_directories(bomberman PRIVATE ${Irrlicht_INCLUDE_DIRS})
  target_link_libraries(bomberman ${Irrlicht_LIBRARIES})
ELSE (NOT Irrlicht_FOUND)
  MESSAGE (FATAL_ERROR, "IRRLICHT NOT FOUND")
ENDIF(Irrlicht_FOUND)