function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(100);
  var cliffData = kobuki.getCliffData();
  console.log('The cliff data is: [' + cliffData.bottom[0] + ', ' + cliffData.bottom[1] + ']');
}
