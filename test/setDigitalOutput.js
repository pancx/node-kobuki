function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

var digitalOutput = {
  values: [false, false, false, false],
  mask: [false, false, false, false] 
};

/**
 * Kobuki has 4xdigital output. This function could set digital output.
 * @param {Object} digitalOutput - Two arrays of boolean value to control the digital output.
 */
kobuki.setDigitalOutput(digitalOutput);
sleep(1000);//It takes some time for command to reach the kobuki.
