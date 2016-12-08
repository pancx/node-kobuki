var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");
var controllerInfoData = {
  type: 0,
  pGain: 100000,
  iGain: 100,
  dGain: 2000
};
console.log('Setting is successful? '+ kobuki.setControllerGain());
console.log('get controller info data '+ kobuki.getControllerGain()); //todo: how to test
var controllerInfoData = kobuki.getControllerInfoData();
console.log('Type is: ' + controllerInfoData.type);
console.log('P gain is: ' + controllerInfoData.pGain);
console.log('I gain is: ' + controllerInfoData.iGain);
console.log('D gain is: ' + controllerInfoData.dGain);