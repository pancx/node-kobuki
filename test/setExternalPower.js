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
 * Kobuki has 4xexternal power. This function could set switch the power.
 * @param {Object} digitalOutput - Two arrays of boolean value for on-off control of the external power.
 */
kobuki.setExternalPower(digitalOutput);
