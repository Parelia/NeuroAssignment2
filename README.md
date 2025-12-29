# Report of the second assignment of Neurorobotics

## Info
This ROS-style package implements the pipeline demanded in the second assignment. It acquires data from a given GDF file, *data.gdf*, and publishes it as **NeuroFrame** messages ([rosneuro_msgs](https://github.com/rosneuro/rosneuro_msgs)) by means of the *acquisition_node*. Each published message represents a chunk of data as `samples x channels`. The file provides data at 512 Hz (sampling rate), and the acquisition is set to have a framerate of 16 Hz, hence, each **NeuroFrame** will contain 32 samples (x channels) of data.

The *my_acquisition.cpp* and *my_filterchain.cpp* files are copies of those from the **RosNeuro** libraries [rosneuro_acquisition](https://github.com/rosneuro/rosneuro_acquisition) and [rosneuro_filters](https://github.com/rosneuro/rosneuro_filters), respectively. The only modifications rely on the input and output topics (to fit the assignment request), and on the insertions of the *main* functions. It has also been created a directory *config* with a YAML file, *MyChainCfg.yaml*, which contains the complete sequence of filters with their parameters to load (necessary for the filterchian node).

// A few new files have been created with an object-oriented style of programming, *bandpower.cpp* and *thresholding.cpp*, and their relative header files, *bandpower.h* and *thresholding.h*.

Here is reported a graph of the relationship between all the project nodes:
![Missing Image](rosgraph.png)

Launch file line of the project:
```
roslaunch threshold_on_bandpower threshold_on_bandpower.launch
```

## Material
Check before starting:
- https://github.com/rosneuro/rosneuro_filters.git
- https://github.com/rosneuro/rosneuro_acquisition.git
- https://wiki.ros.org/ROS/Tutorials/Recording%20and%20playing%20back%20data

## Set Up
Paste and run on the terminal in /home, then open a new terminal in the workspace to start working:
```
echo "source /opt/ros/noetic/setup.bash" >> .bashrc
echo "source devel/setup.bash" >> .bashrc
cd workspaces/rosneuro_ws/src/
rm -r rosneuro_tutorials
git clone https://github.com/rosneuro/rosneuro_acquisition.git
git init
git remote add origin https://github.com/Parelia/NeuroAssignment2.git
git pull origin master --allow-unrelated-histories
```
```
git branch --set-upstream-to=origin/master master
```

## Contributes

