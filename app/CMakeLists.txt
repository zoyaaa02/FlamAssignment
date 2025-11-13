cmake_minimum_required(VERSION 3.10.2)
project("edgeviewer")

add_library(edgeviewer SHARED src/main/cpp/native-lib.cpp)

# OpenCV path
set(OpenCV_DIR "C:/OpenCV-android-sdk/OpenCV-android-sdk/sdk/native/jni")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Find system libraries
find_library(log-lib log)
find_library(android-lib android)
find_library(jnigraphics-lib jnigraphics)   # ✅ Add this line

target_link_libraries(
        edgeviewer
        ${OpenCV_LIBS}
        ${log-lib}
        ${android-lib}
        ${jnigraphics-lib})                 # ✅ Add this line too
