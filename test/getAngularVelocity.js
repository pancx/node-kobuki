function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

while(true)
{
  sleep(100);
  /**
   * Get the angular velocity
   * @return {Number} the angular velocity
   */
  var value = kobuki.getAngularVelocity();
  console.log('The angular velocity is: ' + value);
}
