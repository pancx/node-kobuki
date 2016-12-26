function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/kobuki');

while(true)
{
  sleep(300);
  /**
   * @return {Boollean} wheher kobuki is on.
   */
  console.log('Is alive? ' + kobuki.isAlive());
   /**
   * @return {Boollean} wheher the motors are enabled.
   */
  console.log('Is enabled? ' + kobuki.isEnabled());
  /**
   * @return {Boollean} wheher kobuki is shut down.
   */
  console.log('Is shutdown? ' + kobuki.isShutdown());
}
