# Report of the second assignment of Neurorobotics

## Contributes

## Usage
The package acquires data from external devices and publishes it as a **NeuroFrame** message ([rosneuro_msgs](https://github.com/rosneuro/rosneuro_msgs)). Each published message represents a chunk of data as `samples x channels`. This defines a **framerate** according to which the data is published to other modules. For instance, if the device provides data at 512 Hz (sampling rate) and the acquisition is set to have a framerate of 16 Hz, each **NeuroFrame** will contain 32 samples (x channels) of data.

The following command can be used to launch the package:
```
roslaunch
```
