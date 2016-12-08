function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(100);
  var currentData = kobuki.getCurrentData();
  console.log('The cliff data is: [' + currentData.current[0] + ', ' + currentData.current[1] + ']');
}
