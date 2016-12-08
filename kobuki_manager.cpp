// To add your copyright and license header

#include "kobuki_manager.h"

KobukiManager::KobukiManager() :
  slot_stream_data(&KobukiManager::callNewDataEvent, *this), 
  slot_ros_debug(&KobukiManager::callRosDebug, *this), 
  slot_ros_info(&KobukiManager::callRosInfo, *this), 
  slot_ros_warn(&KobukiManager::callRosWarn, *this), 
  slot_ros_error(&KobukiManager::callRosError, *this), 
  slot_button_event(&KobukiManager::callButtonEvent, *this), 
  slot_bumper_event(&KobukiManager::callBumperEvent, *this), 
  slot_cliff_event(&KobukiManager::callCliffEvent, *this), 
  slot_wheel_event(&KobukiManager::callWheelEvent, *this), 
  slot_power_event(&KobukiManager::callPowerEvent, *this), 
  slot_input_event(&KobukiManager::callInputEvent, *this), 
  slot_robot_event(&KobukiManager::callRobotEvent, *this), 
  slot_version_info(&KobukiManager::callVersionInfo, *this)
{
  kobuki::Parameters parameters; 
  parameters.sigslots_namespace = sigslots_namespace;
  parameters.device_port = "/dev" + sigslots_namespace;
  parameters.enable_acceleration_limiter = false;
  kobuki.init(parameters);
  kobuki.enable();
  //ecl::Sleep()(1);
}

KobukiManager::KobukiManager(const std::string& sigslotsNamespace) :
  slot_stream_data(&KobukiManager::callNewDataEvent, *this), 
  slot_ros_debug(&KobukiManager::callRosDebug, *this), 
  slot_ros_info(&KobukiManager::callRosInfo, *this), 
  slot_ros_warn(&KobukiManager::callRosWarn, *this), 
  slot_ros_error(&KobukiManager::callRosError, *this), 
  slot_button_event(&KobukiManager::callButtonEvent, *this), 
  slot_bumper_event(&KobukiManager::callBumperEvent, *this), 
  slot_cliff_event(&KobukiManager::callCliffEvent, *this), 
  slot_wheel_event(&KobukiManager::callWheelEvent, *this), 
  slot_power_event(&KobukiManager::callPowerEvent, *this), 
  slot_input_event(&KobukiManager::callInputEvent, *this), 
  slot_robot_event(&KobukiManager::callRobotEvent, *this), 
  slot_version_info(&KobukiManager::callVersionInfo, *this)
{
  kobuki::Parameters parameters; 
  sigslots_namespace = sigslotsNamespace;
  parameters.sigslots_namespace = sigslots_namespace;
  parameters.device_port = "/dev" + sigslots_namespace;
  parameters.enable_acceleration_limiter = false;
  kobuki.init(parameters);
  kobuki.enable();
  //ecl::Sleep()(1);
}

KobukiManager::~KobukiManager() {
  kobuki.setBaseControl(0,0); // linear_velocity, angular_velocity in (m/s), (rad/s)
  kobuki.disable();
}

KobukiManager& KobukiManager::operator = (const KobukiManager& rhs) {
  if (&rhs != this) {
    // TODO(widl-nan): copy members from rhs
  }
  return *this;
}

CoreSensorsData KobukiManager::getCoreSensorData() {
  CoreSensorsData coreSensors;
  kobuki::CoreSensors::Data sensor_data = kobuki.getCoreSensorData();
  coreSensors.set_timeStamp(sensor_data.time_stamp);
  coreSensors.set_bumper(sensor_data.bumper);
  coreSensors.set_wheelDrop(sensor_data.wheel_drop);
  coreSensors.set_cliff(sensor_data.cliff);
  coreSensors.set_leftEncoder(sensor_data.left_encoder);
  coreSensors.set_rightEncoder(sensor_data.right_encoder);
  coreSensors.set_leftPwm(sensor_data.left_pwm);
  coreSensors.set_rightPwm(sensor_data.right_pwm);
  coreSensors.set_buttons(sensor_data.buttons);
  coreSensors.set_charger(sensor_data.charger);
  coreSensors.set_battery(sensor_data.battery);
  coreSensors.set_overCurrent(sensor_data.over_current);
  return coreSensors;
}

DockIRData KobukiManager::getDockIRData() {
  ArrayHelper helper;
  DockIRData dock;
  kobuki::DockIR::Data dockir_data = kobuki.getDockIRData();
  helper.FromArrayT(dockir_data.docking.begin(), dockir_data.docking.end());
  dock.set_docking(helper);
  return dock;
}

CliffData KobukiManager::getCliffData() {
  ArrayHelper helper;
  CliffData cliff;
  kobuki::Cliff::Data cliff_data = kobuki.getCliffData();
  helper.FromArrayT(cliff_data.bottom.begin(), cliff_data.bottom.end());
  cliff.set_bottom(helper);
  return cliff;
}

CurrentData KobukiManager::getCurrentData() {
  ArrayHelper helper;
  CurrentData current;
  kobuki::Current::Data current_data = kobuki.getCurrentData();
  helper.FromArrayT(current_data.current.begin(), current_data.current.end());
  current.set_current(helper);
  return current;
}

GpInputData KobukiManager::getGpInputData() {
  ArrayHelper helper;
  GpInputData gpinput;
  kobuki::GpInput::Data gpinput_data = kobuki.getGpInputData();
  helper.FromArrayT(gpinput_data.analog_input.begin(), gpinput_data.analog_input.end());
  gpinput.set_analogInput(helper);
  gpinput.set_digitalInput(gpinput_data.digital_input);
  return gpinput;
}

InertiaData KobukiManager::getInertiaData() {
  ArrayHelper helper;
  InertiaData inertia;
  kobuki::Inertia::Data inertia_data = kobuki.getInertiaData();
  helper.SetT(0,inertia_data.acc[0]);
  helper.SetT(1,inertia_data.acc[1]);
  helper.SetT(2,inertia_data.acc[2]);
  inertia.set_acc(helper);
  inertia.set_angle(inertia_data.angle);
  inertia.set_angleRate(inertia_data.angle_rate);
  return inertia;
}

ThreeAxisGyroData KobukiManager::getRawInertiaData() {
  ArrayHelper helper;
  ThreeAxisGyroData gyro;
  kobuki::ThreeAxisGyro::Data three_axis_gyro = kobuki.getRawInertiaData();
  for (unsigned int i=0; i<three_axis_gyro.followed_data_length; i++)
    helper.SetT(i, three_axis_gyro.data[i]);
  gyro.set_data(helper);
  gyro.set_frameId(three_axis_gyro.frame_id);
  gyro.set_followedDataLength(three_axis_gyro.followed_data_length);
  return gyro;
}

ControllerInfoData KobukiManager::getControllerInfoData() {
  kobuki::ControllerInfo::Data controller_info = kobuki.getControllerInfoData();
  ControllerInfoData controllerInfoData;
  controllerInfoData.set_type(controller_info.type);
  controllerInfoData.set_pGain(controller_info.p_gain);
  controllerInfoData.set_iGain(controller_info.i_gain);
  controllerInfoData.set_dGain(controller_info.d_gain);
  return controllerInfoData;
}

Battery KobukiManager::batteryStatus() {
  kobuki::Battery battery = kobuki.batteryStatus();
  kobuki::Battery::Level level = battery.level();
  Battery batteryStatus;
  if(battery.charging_source == battery.None)
    batteryStatus.set_chargingSource("none");
  else
  {
    if(battery.charging_source == battery.Adapter)
      batteryStatus.set_chargingSource("adapter");
    else
    {
      if(battery.charging_source == battery.Dock)
        batteryStatus.set_chargingSource("dock");
    }
  }
  if(level == battery.Dangerous)
    batteryStatus.set_chargingLevel("dangerous");
  else
  {
    if(level == battery.Low)
      batteryStatus.set_chargingLevel("low");
    else
    {
      if(level == battery.Healthy)
        batteryStatus.set_chargingLevel("healthy");
      else
      {
      if(level == battery.Maximum)
        batteryStatus.set_chargingLevel("maximum");
      }
    }
  }
  if(battery.charging_state == battery.Discharging)
    batteryStatus.set_chargingState("discharging");
  else
  {
    if(battery.charging_state == battery.Charged)
      batteryStatus.set_chargingState("charged");
    else
    {
      if(battery.charging_state == battery.Charging)
        batteryStatus.set_chargingState("charging");
    }
  }

  batteryStatus.set_percent(battery.percent());
  return batteryStatus;
}

double KobukiManager::getHeading() {
  ecl::Angle<double> value = kobuki.getHeading();
  return value;
}

double KobukiManager::getAngularVelocity() {
  return kobuki.getAngularVelocity();
}

VersionInfo KobukiManager::versionInfo() {
  kobuki::VersionInfo version_info = kobuki.versionInfo();
  VersionInfo versionInfo;
  versionInfo.set_firmware(version_info.toString(version_info.firmware));
  versionInfo.set_hardware(version_info.toString(version_info.hardware));
  //versionInfo.set_software(version_info.toString(version_info.software));
  versionInfo.set_software(version_info.getSoftwareVersion());
  versionInfo.set_udid(version_info.toString(version_info.udid0, version_info.udid1, version_info.udid2));
  return versionInfo;
}

WheelJointStates KobukiManager::getWheelJointStates(const WheelJointStates& wheelJointStates) {
  double wheel_left_angle = wheelJointStates.get_wheelLeftAngle();
  double wheel_left_angle_rate = wheelJointStates.get_wheelLeftAngleRate();
  double wheel_right_angle = wheelJointStates.get_wheelRightAngle();
  double wheel_right_angle_rate = wheelJointStates.get_wheelRightAngleRate();
  kobuki.getWheelJointStates(wheel_left_angle, wheel_left_angle_rate, wheel_right_angle, wheel_right_angle_rate);
  WheelJointStates data;
  data.set_wheelLeftAngle(wheel_left_angle);
  data.set_wheelLeftAngleRate(wheel_left_angle_rate);
  data.set_wheelRightAngle(wheel_right_angle);
  data.set_wheelRightAngleRate(wheel_right_angle_rate);
  return data;
}

bool KobukiManager::isAlive() {
  return kobuki.isAlive();
}

bool KobukiManager::isEnabled() {
  return kobuki.isEnabled();
}

bool KobukiManager::isShutdown() {
  return kobuki.isShutdown();
}

void KobukiManager::resetOdometry() {
  kobuki.resetOdometry();
}

void KobukiManager::setBaseControl(const double& linear, const double& angular) {
  kobuki.setBaseControl(linear, angular);
}

void KobukiManager::setLed(const std::string& ledNo, const std::string& ledColor) {
  kobuki::LedNumber no_enum;
  kobuki::LedColour color_enum;
  if (ledNo=="led1")
    no_enum = kobuki::Led1;
  else if (ledNo=="led2")
    no_enum = kobuki::Led2;
  else
    return;
  if (ledColor=="orange")
    color_enum = kobuki::Orange;
  else if (ledColor=="green")
    color_enum = kobuki::Green;
  else if (ledColor=="black")
    color_enum = kobuki::Black;
  else if (ledColor=="red")
    color_enum = kobuki::Red;
  else 
    return;
  kobuki.setLed(no_enum, color_enum);
}

void KobukiManager::setDigitalOutput(const DigitalOutput& digitalOutput) {
  ArrayHelper helper1, helper2;
  helper1 = digitalOutput.get_values();
  helper2 = digitalOutput.get_mask();
  kobuki::DigitalOutput digital_output;
  for(int i = 0; i<4; i++)
  {
    digital_output.values[i] = helper1.GetBoolean(i);//values[i];
    digital_output.mask[i] = helper2.GetBoolean(i);//mask[i];
  }
  kobuki.setDigitalOutput(digital_output);
}

void KobukiManager::setExternalPower(const DigitalOutput& digitalOutput) {
  ArrayHelper helper1, helper2;
  helper1 = digitalOutput.get_values();
  helper2 = digitalOutput.get_mask();
  kobuki::DigitalOutput digital_output;
  for(int i = 0; i<4; i++)
  {
    digital_output.values[i] = helper1.GetBoolean(i);//values[i];
    digital_output.mask[i] = helper2.GetBoolean(i);//mask[i];
  }
  kobuki.setExternalPower(digital_output);
}

void KobukiManager::playSoundSequence(const std::string& soundSequence) {
  kobuki::SoundSequences sound_enum;
  if(soundSequence=="on")
    sound_enum = kobuki::On;
  else if(soundSequence=="off")
      sound_enum = kobuki::Off;
    else if(soundSequence=="recharge")
        sound_enum = kobuki::Recharge;
      else if(soundSequence=="button")
        sound_enum = kobuki::Button;
      else if(soundSequence=="error")
        sound_enum = kobuki::Error;
      else if(soundSequence=="cleaningStart")
        sound_enum = kobuki::CleaningStart;
      else if(soundSequence=="cleaningEnd")
        sound_enum = kobuki::CleaningEnd;
      else
        return;
  kobuki.playSoundSequence(sound_enum);
}

bool KobukiManager::setControllerGain(const ControllerInfoData& controllerInfoData) {
  return kobuki.setControllerGain(controllerInfoData.get_type(), controllerInfoData.get_pGain(), controllerInfoData.get_iGain(), controllerInfoData.get_dGain());
}

bool KobukiManager::getControllerGain() {  
  return kobuki.getControllerGain();
}

PoseUpdateData KobukiManager::updateOdometry() {
  ecl::Pose2D<double> pose_update;
  ecl::linear_algebra::Vector3d pose_update_rates;
  kobuki.updateOdometry(pose_update, pose_update_rates);
  PoseUpdateData poseData;
  pose_ecl *= pose_update;
  poseData.set_dx(pose_update.x());
  poseData.set_dth(pose_update.heading());
  poseData.set_x(pose_ecl.x());
  poseData.set_y(pose_ecl.y());
  poseData.set_heading(pose_ecl.heading());

  return poseData;
}

PoseUpdateData KobukiManager::updateOdometry(const PoseUpdateData& pose) {
  ecl::Pose2D<double> pose_update;
  ecl::linear_algebra::Vector3d pose_update_rates;
  kobuki.updateOdometry(pose_update, pose_update_rates);
  PoseUpdateData poseData;
  pose_ecl.setPose(pose.get_x(), pose.get_y(), pose.get_heading());
  pose_ecl *= pose_update;
  poseData.set_dx(pose_update.x());
  poseData.set_dth(pose_update.heading());
  poseData.set_x(pose_ecl.x());
  poseData.set_y(pose_ecl.y());
  poseData.set_heading(pose_ecl.heading());

  return poseData;
}

// Running in kobuki driver thread
void KobukiManager::callNewDataEvent() {
    KobukiManager* me = this;
    me->async_stream_data.data = me;
    uv_async_send(&async_stream_data);
}

void KobukiManager::callRosDebug(const std::string& ros_debug) {
    KobukiManager* me = this;
    me->ros_debug = ros_debug;
    me->async_ros_debug.data = me;
    uv_async_send(&async_ros_debug);
}

void KobukiManager::callRosInfo(const std::string& ros_info) {
    KobukiManager* me = this;
    me->ros_info = ros_info;
    me->async_ros_info.data = me;
    uv_async_send(&async_ros_info);
}

void KobukiManager::callRosWarn(const std::string& ros_warn) {
    KobukiManager* me = this;
    me->ros_warn = ros_warn;
    me->async_ros_warn.data = me;
    uv_async_send(&async_ros_warn);
}

void KobukiManager::callRosError(const std::string& ros_error) {
    KobukiManager* me = this;
    me->ros_error = ros_error;
    me->async_ros_error.data = me;
    uv_async_send(&async_ros_error);
}

void KobukiManager::callButtonEvent(const kobuki::ButtonEvent& button_event) {
    KobukiManager* me = this;
    me->button_event = button_event;
    me->async_button_event.data = me;
    uv_async_send(&async_button_event);
}

void KobukiManager::callBumperEvent(const kobuki::BumperEvent& bumper_event) {
    KobukiManager* me = this;
    me->bumper_event = bumper_event;
    me->async_bumper_event.data = me;
    uv_async_send(&async_bumper_event);
}

void KobukiManager::callCliffEvent(const kobuki::CliffEvent& cliff_event) {
    KobukiManager* me = this;
    me->cliff_event = cliff_event;
    me->async_cliff_event.data = me;
    uv_async_send(&async_cliff_event);
}

void KobukiManager::callWheelEvent(const kobuki::WheelEvent& wheel_event) {
    KobukiManager* me = this;
    me->wheel_event = wheel_event;
    me->async_wheel_event.data = me;
    uv_async_send(&async_wheel_event);
}

void KobukiManager::callPowerEvent(const kobuki::PowerEvent& power_event) {
    KobukiManager* me = this;
    me->power_event = power_event;
    me->async_power_event.data = me;
    uv_async_send(&async_power_event);
}

void KobukiManager::callInputEvent(const kobuki::InputEvent& input_event) {
    KobukiManager* me = this;
    me->input_event = input_event;
    me->async_input_event.data = me;
    uv_async_send(&async_input_event);
}

void KobukiManager::callRobotEvent(const kobuki::RobotEvent& robot_event) {
    KobukiManager* me = this;
    me->robot_event = robot_event;
    me->async_robot_event.data = me;
    uv_async_send(&async_robot_event);
}

void KobukiManager::callVersionInfo(const kobuki::VersionInfo& version_info) {
    KobukiManager* me = this;
    me->version_info = const_cast<kobuki::VersionInfo*> (&version_info);
    me->async_version_info.data = me;
    uv_async_send(&async_version_info);
}

// Running in v8 thread
void KobukiManager::newDataEvent(uv_async_t *handle) {
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  v8::Local<v8::Value> argv[1] = {
    Nan::New("newdata").ToLocalChecked()
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 1, argv);
}

void KobukiManager::rosDebug(uv_async_t *handle) {
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  v8::Local<v8::Value> argv[2] = {
    Nan::New("debug").ToLocalChecked(), 
    Nan::New(me->ros_debug).ToLocalChecked()
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}


void KobukiManager::rosInfo(uv_async_t *handle) {
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  v8::Local<v8::Value> argv[2] = {
    Nan::New("info").ToLocalChecked(), 
    Nan::New(me->ros_info).ToLocalChecked()
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}


void KobukiManager::rosWarn(uv_async_t *handle) {
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  v8::Local<v8::Value> argv[2] = {
    Nan::New("warn").ToLocalChecked(), 
    Nan::New(me->ros_warn).ToLocalChecked()
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}


void KobukiManager::rosError(uv_async_t *handle) {
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  v8::Local<v8::Value> argv[2] = {
    Nan::New("error").ToLocalChecked(), 
    Nan::New(me->ros_error).ToLocalChecked()
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::buttonEvent(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  std::string button, state;
  switch(me->button_event.button){
    case kobuki::ButtonEvent::Button0 : button = "button0"; break;
    case kobuki::ButtonEvent::Button1 : button = "button1"; break;
    case kobuki::ButtonEvent::Button2 : button = "button2"; break;
  }
  switch(me->button_event.state){
    case kobuki::ButtonEvent::Released : state = "released"; break;
    case kobuki::ButtonEvent::Pressed : state = "pressed"; break;
  } 

  v8::Local<v8::Object> js_button_event = v8::Object::New(isolate);
  js_button_event->Set(v8::String::NewFromUtf8(isolate, "state"), Nan::New(state).ToLocalChecked());
  js_button_event->Set(v8::String::NewFromUtf8(isolate, "button"), Nan::New(button).ToLocalChecked());
  v8::Local<v8::Value> argv[2] = {
    Nan::New("buttonevent").ToLocalChecked(), 
    js_button_event
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::bumperEvent(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  std::string bumper, state;
  switch(me->bumper_event.bumper){
    case kobuki::BumperEvent::Left : bumper = "left"; break;
    case kobuki::BumperEvent::Center : bumper = "center"; break;
    case kobuki::BumperEvent::Right : bumper = "right"; break;
  }
  switch(me->bumper_event.state){
    case kobuki::BumperEvent::Released : state = "released"; break;
    case kobuki::BumperEvent::Pressed : state = "pressed"; break;
  } 

  v8::Local<v8::Object> js_bumper_event = v8::Object::New(isolate);
  js_bumper_event->Set(v8::String::NewFromUtf8(isolate, "state"), Nan::New(state).ToLocalChecked());
  js_bumper_event->Set(v8::String::NewFromUtf8(isolate, "bumper"), Nan::New(bumper).ToLocalChecked());
  v8::Local<v8::Value> argv[2] = {
    Nan::New("bumperevent").ToLocalChecked(), 
    js_bumper_event
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::cliffEvent(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  std::string sensor, state;
  switch(me->cliff_event.sensor){
    case kobuki::CliffEvent::Left : sensor = "left"; break;
    case kobuki::CliffEvent::Center : sensor = "center"; break;
    case kobuki::CliffEvent::Right : sensor = "right"; break;
  }
  switch(me->cliff_event.state){
    case kobuki::CliffEvent::Floor : state = "floor"; break;
    case kobuki::CliffEvent::Cliff : state = "cliff"; break;
  } 

  v8::Local<v8::Object> js_cliff_event = v8::Object::New(isolate);
  js_cliff_event->Set(v8::String::NewFromUtf8(isolate, "state"), Nan::New(state).ToLocalChecked());
  js_cliff_event->Set(v8::String::NewFromUtf8(isolate, "sensor"), Nan::New(sensor).ToLocalChecked());
  v8::Local<v8::Value> argv[2] = {
    Nan::New("cliffevent").ToLocalChecked(), 
    js_cliff_event
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::wheelEvent(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  std::string wheel, state;
  switch(me->wheel_event.wheel){
    case kobuki::WheelEvent::Left : wheel = "left"; break;
    case kobuki::WheelEvent::Right : wheel = "right"; break;
  }
  switch(me->wheel_event.state){
    case kobuki::WheelEvent::Raised : state = "raised"; break;
    case kobuki::WheelEvent::Dropped : state = "dropped"; break;
  } 

  v8::Local<v8::Object> js_wheel_event = v8::Object::New(isolate);
  js_wheel_event->Set(v8::String::NewFromUtf8(isolate, "state"), Nan::New(state).ToLocalChecked());
  js_wheel_event->Set(v8::String::NewFromUtf8(isolate, "wheel"), Nan::New(wheel).ToLocalChecked());
  v8::Local<v8::Value> argv[2] = {
    Nan::New("wheelevent").ToLocalChecked(), 
    js_wheel_event
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::powerEvent(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  std::string event;
  switch(me->power_event.event){
    case kobuki::PowerEvent::Unplugged : event = "unplugged"; break;
    case kobuki::PowerEvent::PluggedToAdapter : event = "pluggedToAdapter"; break;
    case kobuki::PowerEvent::PluggedToDockbase : event = "pluggedToDockbase"; break;
    case kobuki::PowerEvent::ChargeCompleted : event = "chargeCompleted"; break;
    case kobuki::PowerEvent::BatteryLow : event = "batteryLow"; break;
    case kobuki::PowerEvent::BatteryCritical : event = "batteryCritical"; break;
  }

  v8::Local<v8::Object> js_power_event = v8::Object::New(isolate);
  js_power_event->Set(v8::String::NewFromUtf8(isolate, "event"), Nan::New(event).ToLocalChecked());
  v8::Local<v8::Value> argv[2] = {
    Nan::New("powerevent").ToLocalChecked(), 
    js_power_event 
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::inputEvent(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  v8::Local<v8::Array> js_values = v8::Array::New(isolate, 4);
  for(int i = 0; i < 4; i++) {
    js_values->Set(i, v8::Boolean::New(isolate, me->input_event.values[i]));
  }

  v8::Local<v8::Object> js_input_event = v8::Object::New(isolate);
  js_input_event->Set(v8::String::NewFromUtf8(isolate, "values"), js_values);
  v8::Local<v8::Value> argv[2] = {
    Nan::New("inputevent").ToLocalChecked(), 
    js_input_event 
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::robotEvent(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  std::string state;
  switch(me->robot_event.state){
    case kobuki::RobotEvent::Offline : state = "offline"; break;
    case kobuki::RobotEvent::Online : state = "online"; break;
    case kobuki::RobotEvent::Unknown : state = "unknown"; break;
  } 

  v8::Local<v8::Object> js_robot_event = v8::Object::New(isolate);
  js_robot_event->Set(v8::String::NewFromUtf8(isolate, "state"), Nan::New(state).ToLocalChecked());
  v8::Local<v8::Value> argv[2] = {
    Nan::New("robotevent").ToLocalChecked(), 
    js_robot_event 
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

void KobukiManager::versionInfo(uv_async_t *handle) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  Nan::HandleScope scope;
  auto me = static_cast<KobukiManager*>(handle->data);
  v8::Local<v8::Object> js_version_info = v8::Object::New(isolate);
  std::cout<<me->version_info->toString(me->version_info->firmware)<<std::endl; //todo
  js_version_info->Set(v8::String::NewFromUtf8(isolate, "firmware"), Nan::New(me->version_info->toString(me->version_info->firmware)).ToLocalChecked());
  js_version_info->Set(v8::String::NewFromUtf8(isolate, "hardware"), Nan::New(me->version_info->toString(me->version_info->hardware)).ToLocalChecked());
  js_version_info->Set(v8::String::NewFromUtf8(isolate, "software"), Nan::New(me->version_info->getSoftwareVersion()).ToLocalChecked());
  js_version_info->Set(v8::String::NewFromUtf8(isolate, "udid"), Nan::New(me->version_info->toString(me->version_info->udid0, me->version_info->udid1, me->version_info->udid2)).ToLocalChecked());
  //, v8::Boolean::New(isolate, me->input_event.values[i]));

  v8::Local<v8::Value> argv[2] = {
    Nan::New("versioninfo").ToLocalChecked(), 
    js_version_info 
    };
    v8::Local<v8::Object> JavaScriptObj = Nan::New(me->js_this_);
    Nan::MakeCallback(JavaScriptObj, "emit", 2, argv);
}

v8::Handle<v8::Promise>  KobukiManager::connect(const std::string& eventName) {
    if(eventName=="/stream_data") {
      uv_async_init(uv_default_loop(), &async_stream_data, newDataEvent);  
    //callNewDataEvent();//for test
    slot_stream_data.connect(sigslots_namespace + eventName);
  }
    else if(eventName=="/ros_debug") {
      uv_async_init(uv_default_loop(), &async_ros_debug, rosDebug);  
    //callRosDebug(ros_debug);//for test
    slot_ros_debug.connect(sigslots_namespace + eventName);
  } 
    else if(eventName=="/ros_info") {
      uv_async_init(uv_default_loop(), &async_ros_info, rosInfo);  
    //callRosInfo(ros_info);//for test
    slot_ros_info.connect(sigslots_namespace + eventName);
  } 
    else if(eventName=="/ros_warn") {
      uv_async_init(uv_default_loop(), &async_ros_warn, rosWarn);  
    //callRosWarn(ros_warn);//for test
    slot_ros_warn.connect(sigslots_namespace + eventName);
  } 
    else if(eventName=="/ros_error") {
      uv_async_init(uv_default_loop(), &async_ros_error, rosError);  
    //callRosError(ros_error);//for test
    slot_ros_error.connect(sigslots_namespace + eventName);
  } 
  else if(eventName=="/button_event") {
      uv_async_init(uv_default_loop(), &async_button_event, buttonEvent);  
    //callButtonEvent(button_event);//for test
    slot_button_event.connect(sigslots_namespace + eventName);
  }
  else if(eventName=="/bumper_event") {
      uv_async_init(uv_default_loop(), &async_bumper_event, bumperEvent);  
    //callBumperEvent(bumper_event);//for test
    slot_bumper_event.connect(sigslots_namespace + eventName);
  }
  else if(eventName=="/cliff_event") {
      uv_async_init(uv_default_loop(), &async_cliff_event, cliffEvent);  
    //callCliffEvent(cliff_event);//for test
    slot_cliff_event.connect(sigslots_namespace + eventName);
  } 
  else if(eventName=="/wheel_event") {
      uv_async_init(uv_default_loop(), &async_wheel_event, wheelEvent);  
    //callWheelEvent(wheel_event);//for test
    slot_wheel_event.connect(sigslots_namespace + eventName);
  }
  else if(eventName=="/power_event") {
      uv_async_init(uv_default_loop(), &async_power_event, powerEvent);  
    //callPowerEvent(power_event);//for test
    slot_power_event.connect(sigslots_namespace + eventName);
  }
  else if(eventName=="/input_event") {
      uv_async_init(uv_default_loop(), &async_input_event, inputEvent);  
    //callInputEvent(input_event);//for test
    slot_input_event.connect(sigslots_namespace + eventName);
  } 
  else if(eventName=="/robot_event") {
      uv_async_init(uv_default_loop(), &async_robot_event, robotEvent);  
    //callRobotEvent(robot_event);//for test
    slot_robot_event.connect(sigslots_namespace + eventName);
  } 
  else if(eventName=="/version_info") {
      uv_async_init(uv_default_loop(), &async_version_info, versionInfo);  
    //callVersionInfo(*version_info);//for test
    signal_version_info.connect(sigslots_namespace + eventName);
    slot_version_info.connect(sigslots_namespace + eventName);
  }
}

void KobukiManager::disconnect(const std::string& eventName) {
    if(eventName=="/stream_data") {
      uv_close((uv_handle_t*)&async_stream_data, NULL);  
    slot_stream_data.disconnect();
  }
    else if(eventName=="/ros_debug") {
      uv_close((uv_handle_t*)&async_ros_debug, NULL);  
    slot_ros_debug.disconnect();
  } 
    else if(eventName=="/ros_info") {
      uv_close((uv_handle_t*)&async_ros_info, NULL);  
    slot_ros_info.disconnect();
  } 
    else if(eventName=="/ros_warn") {
      uv_close((uv_handle_t*)&async_ros_warn, NULL);  
    slot_ros_warn.disconnect();
  } 
    else if(eventName=="/ros_error") {
      uv_close((uv_handle_t*)&async_ros_error, NULL);  
    slot_ros_error.disconnect();
  } 
  else if(eventName=="/button_event") {
      uv_close((uv_handle_t*)&async_button_event, NULL);  
    slot_button_event.disconnect();
  }
  else if(eventName=="/bumper_event") {
      uv_close((uv_handle_t*)&async_bumper_event, NULL);  
    slot_bumper_event.disconnect();
  }
  else if(eventName=="/cliff_event") {
      uv_close((uv_handle_t*)&async_cliff_event, NULL);  
    slot_cliff_event.disconnect();
  } 
  else if(eventName=="/wheel_event") {
      uv_close((uv_handle_t*)&async_wheel_event, NULL);  
    slot_wheel_event.disconnect();
  }
  else if(eventName=="/power_event") {
      uv_close((uv_handle_t*)&async_power_event, NULL);  
    slot_power_event.disconnect();
  }
  else if(eventName=="/input_event") {
      uv_close((uv_handle_t*)&async_input_event, NULL);  
    slot_input_event.disconnect();
  } 
  else if(eventName=="/robot_event") {
      uv_close((uv_handle_t*)&async_robot_event, NULL);  
    slot_robot_event.disconnect();
  } 
  else if(eventName=="/version_info") {
      uv_close((uv_handle_t*)&async_version_info, NULL);  
    signal_version_info.disconnect();
    slot_version_info.disconnect();
  }
}