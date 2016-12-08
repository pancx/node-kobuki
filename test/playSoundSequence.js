function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

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