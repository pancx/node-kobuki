var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');
/**
 * setControllerGain and getControllerInfoData are about PID control
 * @type {Object} controllerInfoData - The type should be a unsigned 8bit int. pGain, iGain, dGain are unsigned 16bit int
 */
var controllerInfoData = {
  type: 0,
  pGain: 100000,
  iGain: 100,
  dGain: 2000
};
/**
 * @param {Object} controllerInfoData
 * @return {Boolean} whether successful to set controllerInfoData
 */
console.log('Setting is successful? '+ kobuki.setControllerGain(controllerInfoData));
/**
 * @return {Boolean} whether successful to get controllerInfoData
 */
console.log('get controller info data '+ kobuki.getControllerGain()); //todo: how to test
/**
 * @return {Object} controllerInfoData
 */
var controllerInfoData = kobuki.getControllerInfoData();
console.log('Type is: ' + controllerInfoData.type);
console.log('P gain is: ' + controllerInfoData.pGain);
console.log('I gain is: ' + controllerInfoData.iGain);
console.log('D gain is: ' + controllerInfoData.dGain);
