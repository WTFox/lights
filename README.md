# lights

This project provides a customizable LED lighting solution powered by Particle devices (Photon, Argon, etc.). The system allows for dynamic control over LED strips, creating patterns like a fireplace or arc reactor, and adjusting the colors based on the device type. Each pattern is encapsulated in its code file and can be easily configured or extended.

The firmware can be built and deployed using Particle's development environment and OTA flashing. The development setup includes a Makefile for concurrent flashing to multiple devices. The code also accommodates automatic brightness adjustments based on device types.

Detailed setup instructions, usage examples, and troubleshooting steps can be found in the accompanying documentation. Happy lighting!


#### ```/src``` folder:

This is the source folder that contains the firmware files for the project.

#### ```.ino``` file:

This file is the firmware that will runs as the primary application. It contains a `setup()` and `loop()` function.
