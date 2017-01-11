var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');
/**
 * Get the status of the battery.
 * chargingSource: 'none', 'adapter', 'dock'
 * chargingLevel: 'dangerous', 'low', 'healthy', 'maximum'
 * chargingState: 'discharging', 'charged', 'charging'
 * percent: a percent float number of battery voltage, 100% -> capacity / 5% -> dangerous
 * @return {Object} an object with above four menbers 
 */
var battery = kobuki.batteryStatus();
console.log('Charging source is: ' + battery.chargingSource);
console.log('Charging level is: ' + battery.chargingLevel);
console.log('Charging state is: ' + battery.chargingState);
console.log('battery percent is: ' + battery.percent.toFixed(1) + '%');
