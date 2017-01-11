function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

/**
 * play the build-in sound of Kobuki
 * @param {String} SoundSequences - 'on', 'off', 'recharge', 'button', 'error', 'cleaningStart', 'cleaningEnd'.
 */
kobuki.playSoundSequence('on');
sleep(100);
kobuki.playSoundSequence('off');
sleep(100);
kobuki.playSoundSequence('recharge');
sleep(100);
kobuki.playSoundSequence('button');
sleep(100);
kobuki.playSoundSequence('error');
sleep(100);
kobuki.playSoundSequence('cleaningStart');
sleep(100);
kobuki.playSoundSequence('cleaningEnd');
sleep(100);
