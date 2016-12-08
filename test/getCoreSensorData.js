function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

while(true)
{
  sleep(500);
  var sensorData = kobuki.getCoreSensorData();
  console.log('Timestamp is: ' + sensorData.timeStamp);
  console.log('Bumper sensor data is: ' + sensorData.bumper);
  console.log('Wheeldrop sensor data is: ' + sensorData.wheelDrop);
  console.log('Cliff sensor data is: ' + sensorData.cliff);
  console.log('Encoders data is: [' + sensorData.leftEncoder + ', ' + sensorData.rightEncoder +']');
  console.log('PWM data is: [' + sensorData.leftPwm + ', ' + sensorData.rightPwm + ']');
  console.log('Buttons data is: ' + sensorData.buttons);
  console.log('Charger data is: ' + sensorData.charger);
  console.log('Battery data is: ' + sensorData.battery);
  console.log('Overcurrent data is: ' + sensorData.overCurrent);
}
