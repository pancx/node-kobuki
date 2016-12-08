function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

var digitalOutput = {
  values: [false, false, false, false];
  mask: [false, false, false, false];
}

kobuki.setDigitalOutput(digitalOutput);
