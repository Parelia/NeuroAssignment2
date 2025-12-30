cmake_minimum_required(VERSION 3.0.2)
project(threshold_on_bandpower)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  pluginlib
  rosneuro_filters
  rosneuro_acquisition
  rosneuro_msgs
)


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
  include
)


#################
## Executables ##
#################

add_executable(thresholding src/thresholding.cpp)
target_link_libraries(thresholding ${catkin_LIBRARIES})
add_dependencies(thresholding ${catkin_EXPORTED_TARGETS})

add_executable(bandpower src/bandpower.cpp)
target_link_libraries(bandpower ${catkin_LIBRARIES})
add_dependencies(bandpower ${catkin_EXPORTED_TARGETS})

