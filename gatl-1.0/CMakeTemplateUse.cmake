IF(NOT @PROJECT_NAME@_FOUND)
  MESSAGE(FATAL_ERROR "Something went wrong. You are including @UV_LIBRARY_NAME@Use.cmake but @PROJECT_NAME@ was not found.")
ENDIF()


# Make @UV_LIBRARY_NAME@ easier to use.
INCLUDE_DIRECTORIES(${@PROJECT_NAME@_EXTRA_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${@PROJECT_NAME@_INCLUDE_DIRS})

LINK_DIRECTORIES(${@PROJECT_NAME@_EXTRA_LIBRARY_DIRS})
LINK_DIRECTORIES(${@PROJECT_NAME@_LIBRARY_DIRS})

LIST(APPEND EXTRA_INCLUDE_DIRS ${@PROJECT_NAME@_EXTRA_INCLUDE_DIRS} ${@PROJECT_NAME@_INCLUDE_DIRS})
LIST(APPEND EXTRA_LIBRARY_DIRS ${@PROJECT_NAME@_EXTRA_LIBRARY_DIRS} ${@PROJECT_NAME@_LIBRARY_DIRS})

IF(@UV_IS_NOT_TEMPLATE_LIBRARY@)
  LINK_LIBRARIES(${@UV_LIBRARY_NAME@_LIBRARIES})
ENDIF()


# Load the compiler settings used for @UV_LIBRARY_NAME@.
IF(@UV_IS_NOT_TEMPLATE_LIBRARY@ AND @PROJECT_NAME@_BUILD_SETTINGS_FILE)
  INCLUDE(CMakeImportBuildSettings)
  CMAKE_IMPORT_BUILD_SETTINGS(${@PROJECT_NAME@_BUILD_SETTINGS_FILE})
ENDIF()