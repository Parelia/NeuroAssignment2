cmake_minimum_required(VERSION 3.0.2)
project(threshold_on_bandpower)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosneuro_filters
  rosneuro_acquisition
  rosneuro_msgs
)

find_package(Eigen3 REQUIRED)
find_package(PkgConfig)


catkin_package(
  INCLUDE_DIRS include
  #LIBRARIES ${PROJECT_NAME}_myfilter
  CATKIN_DEPENDS roscpp
  #DEPENDS
)


###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
  include
)
add_definitions(${EIGEN3_DEFINITIONS})


#################
## Executables ##
#################

add_executable(thresholding src/thresholding.cpp)
target_link_libraries(thresholding ${catkin_LIBRARIES})
add_dependencies(thresholding ${catkin_EXPORTED_TARGETS})

add_executable(bandpower src/bandpower.cpp)
target_link_libraries(bandpower ${catkin_LIBRARIES})
add_dependencies(bandpower ${catkin_EXPORTED_TARGETS})

add_executable(filterchain src/my_filterchain.cpp)
target_link_libraries(filterchain ${catkin_LIBRARIES})
add_dependencies(filterchain ${catkin_EXPORTED_TARGETS})

add_executable(aquisition src/my_aquisition.cpp)
target_link_libraries(aquisition ${catkin_LIBRARIES})
add_dependencies(aquisition ${catkin_EXPORTED_TARGETS})

