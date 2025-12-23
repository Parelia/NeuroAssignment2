## Set Up
Material to be downloaded:
- https://github.com/rosneuro/rosneuro_tutorials.git
- https://github.com/rosneuro/rosneuro_acquisition.git
- https://github.com/Parelia/NeuroAssignment2.git

Lines to be added to .bashrc to set up console:
- source /opt/ros/noetic/setup.bash
- source devel/setup.bash

Launch file of the project:
- roslaunch src/threshold_on_bandpower/launch/threshold_on_bandpower.launch

___
## Full command line:
echo "source /opt/ros/noetic/setup.bash" >> .bashrc

echo "source devel/setup.bash" >> .bashrc

cd workspaces/rosneuro_ws/src/

rm -r rosneuro_tutorials

git clone https://github.com/Parelia/NeuroAssignment2.git  .

git clone https://github.com/rosneuro/rosneuro_acquisition.git

git clone https://github.com/rosneuro/rosneuro_tutorials.git
