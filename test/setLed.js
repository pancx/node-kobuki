function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

while(true)
{
  /**
   * setLed could control the two Leds in the Kobuki.
   * @param {String} Led number: 'led1', 'led2'
   * @param {String} Led color: 'red', 'orange', 'green', 'black'
   */
  kobuki.setLed('led1', 'red');
  kobuki.setLed('led2', 'orange');
  sleep(500);
  kobuki.setLed('led1', 'orange');
  kobuki.setLed('led2', 'green');
  sleep(500);
  kobuki.setLed('led1', 'green');
  kobuki.setLed('led2', 'black');
  sleep(500);
  kobuki.setLed('led1', 'black');
  kobuki.setLed('led2', 'red');
  sleep(500);
}
