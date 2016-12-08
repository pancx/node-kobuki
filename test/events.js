var addon = require(".././index");
var kobuki = new addon.KobukiManager("/kobuki");

/*kobuki.on("newdata", evt => {
		console.log("got new data");
	});*/

kobuki.on("debug", function(debug) {
    console.log("debug");
    console.log(debug);
  });

kobuki.on("info", function(info) {
    console.log("info");
    console.log(info);
  });

kobuki.on("warn", function(warn) {
    console.log("warn");
    console.log(warn);
  });

kobuki.on("error", function(error) {
    console.log("error");
    console.log(error);
  });

var buttonListener = function(buttonevent) {
    console.log(buttonevent.button, buttonevent.state);
  }

kobuki.on("buttonevent", buttonListener);

kobuki.on("bumperevent", function(bumperevent) {
    console.log(bumperevent.bumper, bumperevent.state);
  });

kobuki.on("cliffevent", function(cliffevent) {
    console.log(cliffevent.sensor, cliffevent.state);
  });

kobuki.on("wheelevent", function(wheelevent) {
    console.log(wheelevent.wheel, wheelevent.state);
  });

kobuki.on("powerevent", function(powerevent) {
    console.log(powerevent.event);
  });

kobuki.on("inputevent", function(inputevent) {
    console.log(inputevent.values[0], inputevent.values[1], inputevent.values[2], inputevent.values[3]);
  });

kobuki.on("robotevent", function(robotevent) {
    console.log(robotevent.state);
  });


kobuki.on("versioninfo", function(versionInfo) {
    console.log(versionInfo.firmware);
    console.log(versionInfo.hardware);
    console.log(versionInfo.software);
    console.log(versionInfo.udid);
  });
/*kobuki.removeListener("buttonevent", buttonListener);
kobuki.removeAllListeners();
kobuki.once("buttonevent", buttonListener);*/

