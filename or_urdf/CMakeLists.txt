cmake_minimum_required(VERSION 3.8)
project(or_urdf)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_EXTENSIONS False)
# add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

list(INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake") 

find_package(srdfdom REQUIRED)
message(STATUS "SRDF FOUND: ${srdfdom_FOUND}")
find_library(srdfdom_LIBRARIES NAMES srdfdom)
list(APPEND srdfdom_INCLUDE_DIRS "/root/xr_phri_ws/install/srdfdom/include/srdfdom")
message(STATUS "srdfdom_INCLUDE_DIRS ${srdf_INCLUDE_DIRS}")
list(APPEND srdfdom_LIBRARY_DIRS "/root/xr_phri_ws/install/srdfdom/lib/srdfdom")
list(APPEND srdfdom_LIBRARIES "/root/xr_phri_ws/install/srdfdom/lib/libsrdfdom.so" "/root/xr_phri_ws/install/srdfdom/lib/libsrdfdom.so.2.0.4")
find_package(urdf REQUIRED)
find_package(Boost REQUIRED COMPONENTS
    filesystem
    system
)
find_package(OpenRAVE REQUIRED)
find_package(TinyXML2 REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${srdfdom_INCLUDE_DIRS}
    ${urdf_INCLUDE_DIRS}
    ${TinyXML2_INCLUDE_DIRS}
    ${OpenRAVE_INCLUDE_DIRS}
)
link_directories(
    ${Boost_LIBRARY_DIRS}
    ${OpenRAVE_LIBRARY_DIRS}
)

add_library("${PROJECT_NAME}_plugin" MODULE
    src/urdf_loader.cpp
    src/ament_finder.cpp
)
set_target_properties(${PROJECT_NAME}_plugin PROPERTIES
    PREFIX ""
    COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}"
    LINK_FLAGS "${OpenRAVE_LINK_FLAGS}"
    LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/lib/openrave-${OpenRAVE_LIBRARY_SUFFIX}")
target_link_libraries("${PROJECT_NAME}_plugin"
    ${Boost_LIBRARIES}
    ${srdfdom_LIBRARIES}
    ${urdf_LIBRARIES}
    ${TinyXML2_LIBRARIES}
    ${OpenRAVE_LIBRARIES}
    srdfdom::srdfdom
)

install(TARGETS "${PROJECT_NAME}_plugin"
    LIBRARY DESTINATION "lib/openrave-${OpenRAVE_LIBRARY_SUFFIX}"
)

ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/ament-env-hooks/20.${PROJECT_NAME}.sh.in")

ament_export_dependencies(srdfdom urdf Boost TinyXML2 OpenRAVE)
ament_export_include_directories(${Boost_INCLUDE_DIRS} ${srdfdom_INCLUDE_DIRS} ${urdf_INCLUDE_DIRS} ${TinyXML2_INCLUDE_DIRS} ${OpenRAVE_INCLUDE_DIRS} srdfdom::srdfdom)
ament_export_libraries(${PROJECT_NAME}_plugin)


ament_package()
