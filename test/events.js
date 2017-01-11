var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

/**
 * This project implements Sigslots by inheriting EventEmitter and overriding addListener and removeListener. 
 * So you can use the same functions of EventEmitter to handle kobuki events.
 * Functions of EventEmitter: addListener, on, once, removeListener, removeAllListeners, setMaxListeners, listeners, emit
 * You can find more details in the official doc of node.js
 * 
 * The following are the events and the data they pass
 * streamdata : informs when a new data packet has arrived from the kobuki
 * - void
 * rosdebug : relay debug messages
 * - String
 * rosinfo : relay info messages
 * - String
 * roswarn : relay warning messages
 * - String
 * roserror : relay error messages
 * - String
 * buttonevent : receive an event when a button state changes
 * -Object, state: 'released', 'pressed'. button: 'button0', 'button1', 'button2'
 * bumperevent : receive an event when the bumper state changes
 * -Object, state: 'released', 'pressed'. bumper: 'left', 'center', 'right'
 * cliffevent : receive an event when a cliff sensor state changes
 * -Object, state: 'floor', 'cliff'. sensor: 'left', 'center', 'right'
 * wheelevent : receive an event when the wheel state (in/out) changes
 * -Object, state: 'raised', 'dropped'. wheel: 'left', 'right'
 * powerevent : receive an event when the power/charging state changes
 * -Object, event: 'unplugged', 'pluggedToAdapter', 'pluggedToDockbase', 'chargeCompleted', 'batteryLow', 'batteryCritical'
 * inputevent : receive an event when the gpio state changes
 * -Object, values : Array of 4 boolean values
 * robotevent : receive an event when the robot state changes
 * -Object, state : 'offline', 'online', 'unknown'
 * versioninfo : receive version info strings on this signal
 * -Object, firmware, hardware, software, udid
 */

// Hint: New data will arrive from the kobuki in 50Hz
/*kobuki.on('newdata', evt => {
		console.log('got new data');
	});*/

kobuki.on('debug', function(debug) {
  console.log('debug');
  console.log(debug);
});

kobuki.on('info', function(info) {
  console.log('info');
  console.log(info);
});

kobuki.on('warn', function(warn) {
  console.log('warn');
  console.log(warn);
});

kobuki.on('error', function(error) {
  console.log('error');
  console.log(error);
});

var buttonListener = function(buttonevent) {
  console.log(buttonevent.button, buttonevent.state);
}

kobuki.on('buttonevent', buttonListener);

kobuki.on('bumperevent', function(bumperevent) {
  console.log(bumperevent.bumper, bumperevent.state);
});

kobuki.on('cliffevent', function(cliffevent) {
  console.log(cliffevent.sensor, cliffevent.state);
});

kobuki.on('wheelevent', function(wheelevent) {
  console.log(wheelevent.wheel, wheelevent.state);
});

kobuki.on('powerevent', function(powerevent) {
  console.log(powerevent.event);
});

kobuki.on('inputevent', function(inputevent) {
  console.log(inputevent.values[0], inputevent.values[1], inputevent.values[2], inputevent.values[3]);
});

kobuki.on('robotevent', function(robotevent) {
  console.log(robotevent.state);
});

// TODO：kobuki will emit versioninfo when powered on，and the event can't be received correctly.
kobuki.on('versioninfo', function(versionInfo) {
  console.log(versionInfo.firmware);
  console.log(versionInfo.hardware);
  console.log(versionInfo.software);
  console.log(versionInfo.udid);
});
/*
kobuki.removeListener('buttonevent', buttonListener);
kobuki.removeAllListeners();
kobuki.once('buttonevent', buttonListener);
*/

