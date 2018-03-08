set (VERSION_MAJOR 0)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)

set(CMAKE_SYSTEM_NAME "Linux")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CXX_COMPILER "${WORKSPACE_ROOT}/opt/fsl-imx-x11/4.1.15-2.0.1/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++")
set(CMAKE_C_COMPILER "${WORKSPACE_ROOT}/opt/fsl-imx-x11/4.1.15-2.0.1/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc")
set(CMAKE_FIND_ROOT_PATH "${WORKSPACE_ROOT}/opt/fsl-imx-x11/4.1.15-2.0.1/sysroots/cortexa9hf-neon-poky-linux-gnueabi/")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
include_directories("${CMAKE_FIND_ROOT_PATH}/usr/include/")
link_directories("${CMAKE_FIND_ROOT_PATH}/usr/lib/")
include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories("${PROJECT_SOURCE_DIR}/build/src/")


set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../output")
set(WIEGANDTEST_SRC
    wiegandtest.c
)

SET(WIEGANDREAD_SRC
	wiegandrw.cpp
)


add_library(WIEGANDRW SHARED ${WIEGANDREAD_SRC})
#add_executable(WIEGANDTEST ${WIEGANDTEST_SRC})

#target_link_libraries(IKUSBSDK -lm)

#set_target_properties(IKUSBSDK PROPERTIES VERSION ${VERSION_MAJOR} SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

#set(CPACK_PACKAGE_NAME "IrisKing")
#set(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
#set(CPACK_PACKAGE_CONTACT "Zhirong Li <lizhr@irisking.com>")
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Build Sample")


