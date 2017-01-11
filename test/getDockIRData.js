function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

while(true)
{
  sleep(100);
  /**
   * Get the dock infrared data
   * @return {Object} DockIRData has docking, array of infrared data
   */
  var dockIRData = kobuki.getDockIRData();
  console.log('The dock IR data is: [' + dockIRData.docking[0] + ', ' + dockIRData.docking[1] + ', ' + dockIRData.docking[2] + ']');
}
