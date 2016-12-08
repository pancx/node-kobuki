var addon = require('.././index');
var kobuki = new addon.KobukiManager("/kobuki");

var battery = kobuki.batteryStatus();
console.log('Charging source is: ' + battery.chargingSource);
console.log('Charging level is: ' + battery.chargingLevel);
console.log('Charging state is: ' + battery.chargingState);
console.log('battery percent is: ' + battery.percent);