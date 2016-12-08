function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

kobuki.setBaseControl(1.0, 0.0);
sleep(1000);
kobuki.setBaseControl(0.0, 1.0);
sleep(3141);
kobuki.setBaseControl(1.0, 0.0);
sleep(1000);
