function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  kobuki.setLed('led1', 'red');
  kobuki.setLed('led2', 'red');
  sleep(500);
  kobuki.setLed('led1', 'orange');
  kobuki.setLed('led2', 'orange');
  sleep(500);
  kobuki.setLed('led1', 'green');
  kobuki.setLed('led2', 'green');
  sleep(500);
  kobuki.setLed('led1', 'black');
  kobuki.setLed('led2', 'black');
  sleep(500);
}
