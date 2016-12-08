function sleep(d){
  for(var t=Date.now(); Date.now() - t <=d;);
}
var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

kobuki.setLed("led1", "red");

var p = {
	x:1,
	y:1,
	heading:1
};

var dx = 0, dth = 0;
var pose = kobuki.updateOdometry(p);

while (true)
{
	sleep(200);
	var pose = kobuki.updateOdometry();
	dx = dx + pose.dx;
	dth = dth + pose.dth;
	console.log("[" + pose.x + ", " + pose.y + ", " + pose.heading + "]");
	console.log("[" + dx + ", " + dth + "]");
}

