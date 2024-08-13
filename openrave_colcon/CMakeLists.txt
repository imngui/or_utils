cmake_minimum_required(VERSION 3.8)
project(openrave_colcon)

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
find_package(openrave REQUIRED)
find_package(srdfdom REQUIRED)

set(BASE_DIRECTORY "openrave-${OpenRAVE_LIBRARY_SUFFIX}")
set(DATA_DIRECTORY "${BASE_DIRECTORY}/data")
set(PLUGINS_DIRECTORY "${BASE_DIRECTORY}/plugins")
set(DATABASES_DIRECTORY "${BASE_DIRECTORY}/databases")

ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/env-hooks/20.${PROJECT_NAME}.sh.in")

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

ament_package()
