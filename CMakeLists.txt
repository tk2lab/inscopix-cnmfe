cmake_minimum_required(VERSION 3.5)
project(cnmfe)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -fPIC")

# cnmfe static library
file(GLOB SRC_FILES
    "src/*.cpp"
    "src/exposed/*.cpp"
    "src/core/*.cpp"
    "src/oasis/*.cpp"
    "src/io/*.cpp"
    "src/utilities/*.cpp"
    "src/log/*.cpp"
)
add_library(${CMAKE_PROJECT_NAME} STATIC ${SRC_FILES})
set(SRC_DIR
    include
    src
    src/exposed
    src/core
    src/oasis
    src/io
    src/utilities
    src/log
)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${SRC_DIR})

# create executable
set(EXECUTABLE_NAME runCnmfe)
add_executable(${EXECUTABLE_NAME} example.cpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${CMAKE_PROJECT_NAME})

# python bindings
if (${BUILD_PYTHON_API})
    set(PYTHON_MODULE_NAME inscopix_cnmfe)
    find_package(Python COMPONENTS Interpreter Development)
    find_package(pybind11 CONFIG)
    pybind11_add_module(${PYTHON_MODULE_NAME} src/api/pythonAPI.cpp)
    target_link_libraries(${PYTHON_MODULE_NAME} PRIVATE ${CMAKE_PROJECT_NAME} pybind11::headers)
endif()

# cnmfe unit tests
if (${BUILD_TEST})
    add_subdirectory(test)
endif()

# use pkg-config
find_package(PkgConfig REQUIRED)

# ThreadPool
get_filename_component(THREADPOOL_HEADER_PATHS lib/ThreadPool ABSOLUTE)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${THREADPOOL_HEADER_PATHS})

# mio
find_package(mio REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC mio::mio)

# nlohmann_json
find_package(nlohmann_json REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

# mkl
#set(BLA_VENDOR Intel10_64lp)
find_package(BLAS REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC BLAS::BLAS)

# opencv
find_package(OpenCV 4.6.0 REQUIRED core imgproc video features2d)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${OpenCV_CFLAGS_OTHER})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${OpenCV_LIBS})

# hdf5
pkg_check_modules(HDF5 REQUIRED hdf5_cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${HDF5_INCLUDE_DIRS})
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${HDF5_CFLAGS_OTHER})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${HDF5_LINK_LIBRARIES})

# libtiff
pkg_check_modules(LIBTIFF REQUIRED libtiff-4)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${LIBTIFF_INCLUDE_DIRS})
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${LIBTIFF_CFLAGS_OTHER})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${LIBTIFF_LINK_LIBRARIES})

# armadillo
pkg_check_modules(ARMADILLO REQUIRED armadillo)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${ARMADILLO_INCLUDE_DIRS})
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ARMA_DONT_USE_WRAPPER ARMA_64BIT_WORD ARMA_BLAS_LONG_LONG ARMA_USE_HDF5 ARMA_NO_DEBUG)
