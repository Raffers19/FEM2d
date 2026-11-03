add_executable(benchmark_fem2d
    benchmark_fem2d.cpp
)

target_link_libraries(benchmark_fem2d PRIVATE fem2d_lib)

if(MSVC)
    target_compile_options(benchmark_fem2d PRIVATE /W4 /EHsc)
endif()