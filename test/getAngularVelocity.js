function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(100);
  var value = kobuki.getAngularVelocity();
  console.log('The angular velocity is: ' + value);
}
