var addon = require('../index');
var kobuki = new addon.KobukiManager('/kobuki');

/**
 * Get the version info of firmware, hardware and software, and the udid of Kobuki.
 * @return {Object} VersionInfo has four string members, firmware, hardware, software, and udid.
 */
var versionInfo = kobuki.versionInfo();
console.log('The firmware is: ' + versionInfo.firmware);
console.log('The hardware is: ' + versionInfo.hardware);
console.log('The software is: ' + versionInfo.software);
console.log('The udid is: ' + versionInfo.udid);