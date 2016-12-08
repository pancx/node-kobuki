var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

var versionInfo = kobuki.versionInfo();
console.log('The firmware is: ' + versionInfo.firmware);
console.log('The hardware is: ' + versionInfo.hardware);
console.log('The software is: ' + versionInfo.software);
console.log('The udid is: ' + versionInfo.udid);