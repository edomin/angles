function(link_target TARGET)
    set(ARG_NUM 1)
    while (${ARG_NUM} LESS ${ARGC})
        list(APPEND SOURCES ${ARGV${ARG_NUM}})
        math(EXPR ARG_NUM "${ARG_NUM} + 1")
    endwhile()

    add_executable(${TARGET} ${SOURCES})
endfunction()

function(ang_process_flag_availability ANG_FLAG_VALUE ANG_FLAG
    ANG_FALLBACK_FLAG
)
    if(DEFINED ${ANG_FLAG_VALUE})
        return()
    endif()

    message(STATUS "Check if C++ compiler accepts ${ANG_FLAG}")

    file(WRITE "${CMAKE_BINARY_DIR}/trycompile.cpp"
        "int main(int argc, char **argv) {return 0;}")
    string(REPLACE " " ";" ANG_FLAG_LIST ${ANG_FLAG})
    execute_process(
        COMMAND
            ${CMAKE_CXX_COMPILER} ${ANG_FLAG_LIST}
            -c "${CMAKE_BINARY_DIR}/trycompile.cpp"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE ANG_EXECUTE_RESULT
        # OUTPUT_VARIABLE ANG_EXECUTE_OUTPUT
        # ERROR_VARIABLE ANG_EXECUTE_ERROR
        OUTPUT_QUIET
        ERROR_QUIET
    )
    # message(STATUS ${ANG_EXECUTE_OUTPUT})
    # message(STATUS ${ANG_EXECUTE_ERROR})

    if (NOT ANG_EXECUTE_RESULT) # exitcode 0 - gcc success
        set(ANG_HAVE_FLAG ON)
    else()
        set(ANG_HAVE_FLAG OFF)
    endif()
    file (REMOVE "${CMAKE_BINARY_DIR}/trycompile.cpp")
    if (${ANG_HAVE_FLAG})
        message(STATUS "Check if C++ compiler accepts ${ANG_FLAG} - yes")
        set(${ANG_FLAG_VALUE} ${ANG_FLAG_LIST} CACHE STRING "")
    else()
        message(STATUS "Check if C++ compiler accepts ${ANG_FLAG} - no")
        set(${ANG_FLAG_VALUE} ${ANG_FALLBACK_FLAG} CACHE STRING "")
    endif()
endfunction()
