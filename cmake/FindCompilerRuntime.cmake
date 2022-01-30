# COMPILER_RUNTIME_FOUND - true if library and headers were found
# COMPILER_RUNTIME_LIBRARIES - library directories

if (COMPILER_RUNTIME_LIBRARIES)
    set(COMPILER_RUNTIME_FOUND TRUE)
else ()
    message(STATUS "Looking for compiler runtime libraries/options")

    ang_process_flag_availability(STATIC_LIBGCC "-static-libgcc" "" QUIET)
    if (STATIC_LIBGCC)
        set(COMPILER_RUNTIME_LIBRARIES ${STATIC_LIBGCC} CACHE STRING "")
    else()
        ang_process_flag_availability(RTLIB_COMPILER_RT "--rtlib=compiler-rt"
            "" QUIET)
        if (RTLIB_COMPILER_RT)
            set(COMPILER_RUNTIME_LIBRARIES ${RTLIB_COMPILER_RT} CACHE STRING "")
        endif()
    endif()

    if (COMPILER_RUNTIME_LIBRARIES)
        message(STATUS
            "Looking for compiler runtime libraries/options - ${COMPILER_RUNTIME_LIBRARIES}")
        set(COMPILER_RUNTIME_FOUND TRUE)
    else()
        message(STATUS
            "Looking for compiler runtime libraries/options - not found")
        message(FATAL_ERROR "Could not find compiler runtime libraries/options")
    endif()
endif ()
