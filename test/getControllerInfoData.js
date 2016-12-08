var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

var controllerInfoData = kobuki.getControllerInfoData();
console.log('Type is: ' + controllerInfoData.type);
console.log('P gain is: ' + controllerInfoData.pGain);
console.log('I gain is: ' + controllerInfoData.iGain);
console.log('D gain is: ' + controllerInfoData.dGain);