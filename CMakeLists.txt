cmake_minimum_required(VERSION 3.2)

set(PATHS . )
set(NAME_EXECUTABLE "matrix")
set(NAME_TEST "test_matrix")


if ($ENV{GITHUB_RUN_NUMBER})
	project(${NAME_EXECUTABLE} VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
	project(${NAME_EXECUTABLE} VERSION 0.0.1)
endif()


find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(${NAME_EXECUTABLE} main.cpp)
add_executable(${NAME_TEST} test.cpp)


set_target_properties(${NAME_EXECUTABLE} ${NAME_TEST} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${NAME_EXECUTABLE}
    PRIVATE "${PATHS}"
)


set_target_properties(${NAME_TEST} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(${NAME_EXECUTABLE} PRIVATE
    
)

target_link_libraries(${NAME_TEST}
    ${Boost_LIBRARIES}    
)


if (MSVC)
    target_compile_options(${NAME_EXECUTABLE} PRIVATE
        /W4
    )
    target_compile_options(${NAME_TEST} PRIVATE
        /W4
    )
else ()
    target_compile_options(${NAME_EXECUTABLE} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${NAME_TEST} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ${NAME_EXECUTABLE} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT evgeniy.yurevich@gmail.com)

include(CPack)

enable_testing()

add_test(${NAME_TEST} ${NAME_TEST})
