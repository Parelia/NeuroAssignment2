cmake_minimum_required(VERSION 3.0.2)
project(threshold_on_bandpower)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  pluginlib
  rosneuro_filters
  rosneuro_acquisition
  rosneuro_msgs
)

find_package(Eigen3 REQUIRED)
find_package(PkgConfig)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp pluginlib rosneuro_filters rosneuro_acquisition rosneuro_msgs
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

add_executable(my_filterchain src/my_filterchain.cpp)
target_link_libraries(my_filterchain ${catkin_LIBRARIES})
add_dependencies(my_filterchain ${catkin_EXPORTED_TARGETS})

add_executable(my_acquisition src/my_acquisition.cpp)
target_link_libraries(my_acquisition ${catkin_LIBRARIES})
add_dependencies(my_acquisition ${catkin_EXPORTED_TARGETS})

