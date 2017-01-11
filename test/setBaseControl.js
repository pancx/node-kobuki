function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

/**
 * Send the speed control command to Kobuki
 * @param {Number} linear velocity in m/s
 * @param {Number} angular velocity in rad/s
 */
kobuki.setBaseControl(0.5, 0.0);
sleep(2000);
kobuki.setBaseControl(0.0, 1.0);
sleep(3141);
kobuki.setBaseControl(0.5, 0.0);
sleep(2000);
kobuki.setBaseControl(0.0, 0.0);
sleep(1000);
