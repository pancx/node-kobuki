function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(100);
  var gpInputData = kobuki.getGpInputData();
  console.log('The digital input data is: [' + gpInputData.digitalInput + ']');
  console.log('The analog input data is: [' + gpInputData.analogInput[0] + ', ' + gpInputData.analogInput[1] + ', ' + gpInputData.analogInput[2] +  gpInputData.analogInput[3] + ']');
}
