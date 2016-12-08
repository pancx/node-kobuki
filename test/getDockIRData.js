function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(100);
  var dockIRData = kobuki.getDockIRData();
  console.log('The dock IR data is: [' + dockIRData.docking[0] + ', ' + dockIRData.docking[1] + ', ' + dockIRData.docking[2] + ']');
}
