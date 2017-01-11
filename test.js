function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}

var addon = require('./build/Release/node-kobuki');
var kobuki = new addon.KobukiManager("/ttyUSB0");
//var kobuki = new Kobuki();
kobuki.setLed("led1", "red");
//kobuki.setBaseControl(-0.1, 0.2);

while(1)
{
  sleep(200);
  var pose = kobuki.updateOdometry();
  console.log(pose.x);
  console.log(pose.y);
  console.log(pose.heading);
}
