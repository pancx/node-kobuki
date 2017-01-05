var addon = require('../index');
var kobuki = new addon.KobukiManager('/kobuki');

/**
 * todo: how to test?
 */
kobuki.resetOdometry();
addon.sleep(1000);//It takes some time for command to reach the kobuki.

