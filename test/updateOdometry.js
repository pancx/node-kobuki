function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require('../index');
var kobuki = new addon.KobukiManager('/kobuki');

kobuki.setLed('led1', 'red');

var p = {
	x:1,
	y:1,
	heading:1
};

var dx = 0, dth = 0;

/**
 * updateOdometry will return new pose, x, y and hending, and the increment of mileage and heading from last call of updateOdometry.
 * pose is updated all the time from Kobuki is started.
 * @param {Object} p - manually reset the odometry, it can also be null.
 * @return {Object} new pose
 */
var pose = kobuki.updateOdometry(p);

while (true)
{
	sleep(200);
	var pose = kobuki.updateOdometry();
	dx = dx + pose.dx;
	dth = dth + pose.dth;
	console.log('[' + pose.x + ', ' + pose.y + ', ' + pose.heading + ']');
	console.log('[' + dx + ', ' + dth + ']');
}

