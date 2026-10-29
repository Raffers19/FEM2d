# Create the FEM library
add_library(fem2d_lib STATIC
    mesh/mesh_funcs.cpp
    mesh/mesher.cpp
    quadrature/quad_funcs.cpp
    quadrature/quad.cpp
    assembley/assembler.cpp
)

# Make public headers accessible
target_include_directories(fem2d_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Require C++20
target_compile_features(fem2d_lib PUBLIC cxx_std_20)

# Build the simulation executable
add_executable(fem2d
    main.cpp
)

# Link the simulation to the libraries
target_link_libraries(fem2d PRIVATE fem2d_lib)

# Enable compiler warnings
if(MSVC)
    target_compile_options(fem2d_lib PRIVATE /W4)
    target_compile_options(fem2d PRIVATE /W4)

endif()