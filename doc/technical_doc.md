# Documentación Técnica

## ¿Cómo usar las librerías externas con CMake?

### Box2D
```CMake
add_library(<LIBRARY_NAME>
    <FILE_1>
    ...
    <FILE_N>
)

target_link_libraries(<LIBRARY_NAME>
    box2d
)
```

### SDL
```CMake
include_directories(${SDL2PP_INCLUDE_DIRS})

add_library(<LIBRARY_NAME>
    <FILE_1>
    ...
    <FILE_N>
)

target_link_libraries(<LIBRARY_NAME>
    ${SDL2PP_LIBRARIES}
)
```

### GTest
```CMake
enable_testing()

add_executable(<TEST_EXE>
    <FILE_1>
    ...
    <FILE_N>
)

target_link_libraries(<TEST_EXE>
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(<TEST_EXE>)
```