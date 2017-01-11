var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

/**
 * Get the PID control info data
 * @return {Object} ControllerInfoData: type, pGain, iGain, dGain. The type should be a unsigned 8bit int. pGain, iGain, dGain are unsigned 16bit int
 */
var controllerInfoData = kobuki.getControllerInfoData();
console.log('Type is: ' + controllerInfoData.type);
console.log('P gain is: ' + controllerInfoData.pGain);
console.log('I gain is: ' + controllerInfoData.iGain);
console.log('D gain is: ' + controllerInfoData.dGain);
