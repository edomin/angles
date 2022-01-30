# WINPTHREAD_FOUND - true if library and headers were found
# WINPTHREAD_LIBRARIES - library directories

if (WINPTHREAD_LIBRARIES)
    set(WINPTHREAD_FOUND TRUE)
else ()
    message(STATUS "Looking for static winpthread options")

    ang_process_flag_availability(STATIC_WINPTHREAD
        "-Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive" ""
        QUIET)
    if (STATIC_WINPTHREAD)
        set(WINPTHREAD_LIBRARIES ${STATIC_WINPTHREAD} CACHE STRING "")
    endif()

    if (WINPTHREAD_LIBRARIES)
        message(STATUS
            "Looking for static winpthread options - ${WINPTHREAD_LIBRARIES}")
        set(WINPTHREAD_FOUND TRUE)
    else()
        message(STATUS "Looking for static winpthread options - not found")
        message(FATAL_ERROR "Could not find static winpthread options")
    endif()
endif ()
