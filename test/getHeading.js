function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(100);
  var heading = kobuki.getHeading();
  console.log('The heading is: ' + heading);
}
