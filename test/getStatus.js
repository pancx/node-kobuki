function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(300);
  console.log('Is alive? ' + kobuki.isAlive());
  console.log('Is enabled? ' + kobuki.isEnabled());
  console.log('Is shutdown? ' + kobuki.isShutdown());
}
