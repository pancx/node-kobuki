function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');

while(true)
{
  sleep(500);
  /**
   * Get raw inertia data
   * @return {Object} ThreeAxisGyroData has frameId, followedDataLength and data
   */
  var inertiaData = kobuki.getRawInertiaData();
  console.log('The frameId is: [' + inertiaData.frameId + ']');
  console.log('The followed data Length is: [' + inertiaData.followedDataLength + ']');
  var i = 0;
  console.log('The inertia data is: ');
  while (i<inertiaData.followedDataLength)
  {
  	console.log(inertiaData.data[i]);
    i=i+1;
  }
}
