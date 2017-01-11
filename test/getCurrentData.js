function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

while(true)
{
  sleep(100);
  /**
   * Get the current data
   * @return {Object} CurrentData has current, array of current data
   */
  var currentData = kobuki.getCurrentData();
  console.log('The cliff data is: [' + currentData.current[0] + ', ' + currentData.current[1] + ']');
}
