var sleep = function sleep(d){
	for(var t=Date.now(); Date.now() - t <=d;);
}

var addon = require('./build/Release/node-kobuki');
var KobukiManager = null;
KobukiManager=addon.KobukiManager;

var EventEmitter = require('events').EventEmitter;
function inherits(target, source) {
    for (var k in source.prototype) {
        target.prototype[k] = source.prototype[k];
    }
}

inherits(KobukiManager, EventEmitter);

KobukiManager.prototype.addListener = function(type, listener) {
  switch(type) {
    case "newdata" : this.connect("/stream_data"); break;
    case "debug" : this.connect("/ros_debug"); break;
    case "info" : this.connect("/ros_info"); break;
    case "warn" : this.connect("/ros_warn"); break;
    case "error" : this.connect("/ros_error"); break;
    case "buttonevent" : this.connect("/button_event"); break;
    case "bumperevent" : this.connect("/bumper_event"); break;
    case "cliffevent" : this.connect("/cliff_event"); break;
    case "wheelevent" : this.connect("/wheel_event"); break;
    case "powerevent" : this.connect("/power_event"); break;
    case "inputevent" : this.connect("/input_event"); break;
    case "robotevent" : this.connect("/robot_event"); break;
    case "versioninfo" : this.connect("/version_info"); break;
  }
	
  var m;
  var events;
  var existing;

  if (typeof listener !== 'function')
    throw new TypeError('listener must be a function');

  events = this._events;
  if (!events) {
    events = this._events = {};
    this._eventsCount = 0;
  } else {
    // To avoid recursion in the case that type === "newListener"! Before
    // adding it to the listeners, first emit "newListener".
    if (events.newListener) {
      this.emit('newListener', type,
                listener.listener ? listener.listener : listener);

      // Re-assign `events` because a newListener handler could have caused the
      // this._events to be assigned to a new object
      events = this._events;
    }
    existing = events[type];
  }

  if (!existing) {
    // Optimize the case of one listener. Don't need the extra array object.
    existing = events[type] = listener;
    ++this._eventsCount;
  } else {
    if (typeof existing === 'function') {
      // Adding the second element, need to change to array.
      existing = events[type] = [existing, listener];
    } else {
      // If we've already got an array, just append.
      existing.push(listener);
    }

    // Check for listener leak
    if (!existing.warned) {
      m = $getMaxListeners(this);
      if (m && m > 0 && existing.length > m) {
        existing.warned = true;
        console.error('(node) warning: possible EventEmitter memory ' +
                      'leak detected. %d %s listeners added. ' +
                      'Use emitter.setMaxListeners() to increase limit.',
                      existing.length, type);
        console.trace();
      }
    }
  }

  return this;
}

KobukiManager.prototype.on = KobukiManager.prototype.addListener;

// emits a 'removeListener' event iff the listener was removed
KobukiManager.prototype.removeListener =
    function (type, listener) {
      switch(type) {
        case "newdata" : this.disconnect("/stream_data"); break;
        case "debug" : this.disconnect("/ros_debug"); break;
        case "info" : this.disconnect("/ros_info"); break;
        case "warn" : this.disconnect("/ros_warn"); break;
        case "error" : this.disconnect("/ros_error"); break;
        case "buttonevent" : this.disconnect("/button_event"); break;
        case "bumperevent" : this.disconnect("/bumper_event"); break;
        case "cliffevent" : this.disconnect("/cliff_event"); break;
        case "wheelevent" : this.disconnect("/wheel_event"); break;
        case "powerevent" : this.disconnect("/power_event"); break;
        case "inputevent" : this.disconnect("/input_event"); break;
        case "robotevent" : this.disconnect("/robot_event"); break;
        case "versioninfo" : this.disconnect("/version_info"); break;
      }

      var list, events, position, i;

      if (typeof listener !== 'function')
        throw new TypeError('listener must be a function');

      events = this._events;
      if (!events)
        return this;

      list = events[type];
      if (!list)
        return this;

      if (list === listener || (list.listener && list.listener === listener)) {
        if (--this._eventsCount === 0)
          this._events = {};
        else {
          delete events[type];
          if (events.removeListener)
            this.emit('removeListener', type, listener);
        }
      } else if (typeof list !== 'function') {
        position = -1;

        for (i = list.length; i-- > 0;) {
          if (list[i] === listener ||
              (list[i].listener && list[i].listener === listener)) {
            position = i;
            break;
          }
        }

        if (position < 0)
          return this;

        if (list.length === 1) {
          list[0] = undefined;
          if (--this._eventsCount === 0) {
            this._events = {};
            return this;
          } else {
            delete events[type];
          }
        } else {
          spliceOne(list, position);
        }

        if (events.removeListener)
          this.emit('removeListener', type, listener);
      }

      return this;
};

exports.sleep = sleep;
exports.KobukiManager = KobukiManager;