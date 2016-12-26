function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/kobuki');

var digitalOutput = {
  values: [false, false, false, false];
  mask: [false, false, false, false];
}

/**
 * Kobuki has 4xdigital output. This function could set digital output.
 * @param {Object} digitalOutput - Two arrays of boolean value to control the digital output.
 */
kobuki.setDigitalOutput(digitalOutput);