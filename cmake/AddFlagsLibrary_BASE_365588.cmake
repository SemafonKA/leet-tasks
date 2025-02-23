#
# This macro will add interface lib with compiler options and C++ standart
#

macro(AddFlagsLibrary LIB_NAME)
    add_library(${LIB_NAME} INTERFACE)
    target_compile_features(${LIB_NAME} INTERFACE cxx_std_20)

    # Устанавливаем флаги компиляции
    if(MSVC) # Отдельно для Visual Studio 
        target_compile_options(${LIB_NAME} INTERFACE "/W4" "$<$<CONFIG:RELEASE>:/O2>")
    else() # Отдельно для остальных
        target_compile_options(${LIB_NAME} INTERFACE "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")

        # Если это компилятор Clang, отдельно указываем используемые библиотеки
        if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            target_compile_options(${LIB_NAME} INTERFACE "-stdlib=libc++")
        else()
            # nothing special for gcc at the moment
        endif()
    endif()
endmacro()
