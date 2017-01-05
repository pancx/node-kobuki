Node-kobuki
===========

Kobuki is a lowcost mobile research robot. Kobuki has highly reliable odometry and long battery hours and provides power for an external sensor and actuator. This project aims to implement the control of kobuki by using node.js and offer apis for javascript developers.   

#Installation:
Install the following basic dependencies refer to their official pages.<br>
1. [Node.js](https://nodejs.org/en/)<br>
    Node.js® is a JavaScript runtime built on Chrome's V8 JavaScript engine. Node.js uses an event-driven, non-blocking I/O model that makes it lightweight and efficient. Recommend that download the source of stable version, compile and install. <br>
2. [node-gyp](https://www.npmjs.com/package/node-gyp)<br>
    node-gyp is a cross-platform command-line tool written in Node.js for compiling native addon modules for Node.js.<br>
    You can install with npm:<br>
    ```
    $ npm install -g node-gyp
    ```<br>
3. [Kobuki linux driver](https://yujinrobot.github.io/kobuki/doxygen/enInstallationLinuxGuide.html)<br>
    Install the kobuki driver for Linux.<br>
    (You may need to install some dependencies like libftdi-dev and libusb-dev.)<br>
4. [widl-nan](https://github.com/01org/widl-nan)<br>
    This toolchain transcompiles W3C Web IDL and Version 2 to the NAN C++ code. This tool improve efficiency of Node.js Addon developing, allows developers focus on spec definition and actual implementation codes.<br>
    Clone this project to your workspace and install widl-nan. Notice the step `Compile your Web IDL`, repalce it by:<br>
    ```
    $ ./node_modules/.bin/widl-nan kobuki.widl
    ```<br>
    And do not init helper files.<br>


#Kobuki APIs
You can find its native apis on its official page [kobuki_driver: Getting Started](https://yujinrobot.github.io/kobuki/doxygen/enGettingStartedGuide.html). <br>
This project provides javascript apis and try best to ensure their names, args and return values seem as the native apis.<br>

##**Raw Data**

The kobuki driver runs a background thread which continually retrieves packets from the kobuki, saving the raw data, and additionally doing some processing before updating the current state of the robot.

Raw data can be accessed at any time by one of the following getXXX commands:

**getCoreSensorData**<br>
**getDockIRData**<br>
**getCliffData**<br>
**getCurrentData**<br>
**getGpInputData**<br>
**getInertiaData**<br>
**getRawInertiaData**<br>
**getControllerInfoData**<br>
The gyro provides both filtered yaw angle as well as unfiltered 3-axis inertial data hence the two calls above.

##**Processed Data and Status**

The following are convenience methods for accessing the current state of the robot

**batteryStatus**<br>
**getHeading**<br>
**getAngularVelocity**<br>
**versionInfo** : hardware, firmware and software version strings.<br>
**getWheelJointStates**<br>
**isAlive** : true if a kobuki is detected and streaming data.<br>
**isEnabled** : true if the motor power is enabled<br>
**isShutdown** : true if the worker threads for this driver have been shut down.<br>

##**Soft Commands**

**resetOdometry**<br>

##**Hard Commands**

**setBaseControl**<br>
**setLed**<br>
**setDigitalOutput**<br>
**setExternalPower**<br>
**playSoundSequence**<br>
**setControllerGain**<br>
**getControllerGain**<br>

##**The Differential Drive Module**

The final function of importance is the **updateOdometry** method. This updates the current odometry state of the robot, fusing encoder and gyro heading data with the previous known state. For deterministic odometry, it is important this method is called each time a new data packet from the kobuki arrives. Refer to the simple control loop example for more information and working code to illustrate.

##**Events**

Sigslots are the primary way of kobuki driver to handle events emitted by the kobuki driver (c.f. with the usual function callbacks with void function pointers as arguments). You can go straight to the official documentation [Sigslots](https://yujinrobot.github.io/kobuki/doxygen/enSigslotsGuide.html) and [ecl_sigslots](http://wiki.ros.org/ecl_sigslots) to find more information. It provided an asynchronous way to control the robot indeed.　This project implements Sigslots by inheriting EventEmitter(learn more in its page [EventEmitter](https://www.npmjs.com/package/events)) and overriding **addListener** and **removeListener**. <br>

The following represent the available events

* **streamdata** : informs when a new data packet has arrived from the kobuki
* **rosdebug** : relay debug messages
* **rosinfo** : relay info messages
* **roswarn** : relay warning messages
* **roserror** : relay error messages
* **buttonevent** : receive an event when a button state changes
* **bumperevent** : receive an event when the bumper state changes
* **cliffevent** : receive an event when a cliff sensor state changes
* **wheelevent** : receive an event when the wheel state (in/out) changes
* **powerevent** : receive an event when the power/charging state changes
* **inputevent** : receive an event when the gpio state changes
* **robotevent** : receive an event when the robot state changes
* **versioninfo** : receive version info strings on this signal


#Test & usage cases

Refer to the cases in the `test` folder to learn more usage of the javascript apis.
```
$ node test.js
```
