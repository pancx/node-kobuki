function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/ttyUSB0');
var wheelJointStates = {
  wheelLeftAngle: 0,
  wheelLeftAngleRate: 0,
  wheelRightAngle: 0,
  wheelRightAngleRate: 0
};
while(true)
{
  sleep(200);
  /**
   * @param {Object} wheelJointStates - defined as above
   * @return {Object} WheelJointStates
   */
  wheelJointStates = kobuki.getWheelJointStates(wheelJointStates);
  console.log('Wheel left angle is: ' + wheelJointStates.wheelLeftAngle);
  console.log('Wheel left angle rate is: ' + wheelJointStates.wheelLeftAngleRate);
  console.log('Wheel right angle is: ' + wheelJointStates.wheelRightAngle);
  console.log('Wheel right angle rate is: ' + wheelJointStates.wheelRightAngleRate);
}
