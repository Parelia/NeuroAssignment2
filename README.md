# Report of the second assignment of Neurorobotics

## Info
The package acquires data from external devices and publishes it as a **NeuroFrame** message ([rosneuro_msgs](https://github.com/rosneuro/rosneuro_msgs)). Each published message represents a chunk of data as `samples x channels`. This defines a **framerate** according to which the data is published to other modules. For instance, if the device provides data at 512 Hz (sampling rate) and the acquisition is set to have a framerate of 16 Hz, each **NeuroFrame** will contain 32 samples (x channels) of data.

Graph of the relationship between the project nodes:
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

