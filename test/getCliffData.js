function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/kobuki');

while(true)
{
  sleep(100);
  /**
   * Get the cliff sensors' data
   * @return {Object} CliffData has one menber, bottom, which is array of left, right and center cliff sensors' data.
   */
  var cliffData = kobuki.getCliffData();
  console.log('The cliff data is: [' + cliffData.bottom[0] + ', ' + cliffData.bottom[1] + ', ' + cliffData.bottom[2] + ']');
}
