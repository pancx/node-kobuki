function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(100);
  var inertiaData = kobuki.getInertiaData();
  console.log('The angle is: [' + inertiaData.angle + ']');
  console.log('The angleRate is: [' + inertiaData.angleRate + ']');
  console.log('The inertia data is: [' + inertiaData.acc[0] + ', ' + inertiaData.acc[1] + ', ' + inertiaData.acc[2] + ']');
}
