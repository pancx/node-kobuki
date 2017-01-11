function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

while(true)
{
  sleep(100);
  /**
   * Get the heading of Kobuki
   * @return {Number} the heading of Kobuki
   */
  var heading = kobuki.getHeading();
  console.log('The heading is: ' + heading);
}
