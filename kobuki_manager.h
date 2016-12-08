// To add your copyright and license header

#ifndef _KOBUKI_MANAGER_H_
#define _KOBUKI_MANAGER_H_

#include <node.h>
#include <v8.h>

#include <csignal>
#include <ecl/time.hpp>
#include <ecl/sigslots.hpp>
#include <ecl/geometry/pose2d.hpp>
#include <ecl/linear_algebra.hpp>
#include "kobuki_driver/kobuki.hpp"
#include <string>

#include "gen/generator_helper.h"
#include "gen/array_helper.h"

#include "gen/core_sensors_data.h"

#include "gen/dockir_data.h"

#include "gen/cliff_data.h"

#include "gen/current_data.h"

#include "gen/gp_input_data.h"

#include "gen/inertia_data.h"

#include "gen/three_axis_gyro_data.h"

#include "gen/controller_info_data.h"

#include "gen/battery.h"

#include "gen/version_info.h"

#include "gen/wheel_joint_states.h"

#include "gen/digital_output.h"

#include "gen/pose_update_data.h"

//#include "gen/thread-event-helper.h"
#include "gen/promise-helper.h"

class KobukiManager {
 public:
  KobukiManager();

  explicit KobukiManager(const std::string& sigslotsNamespace);

  ~KobukiManager();

  KobukiManager& operator = (const KobukiManager& rhs);

 public:
  //kobuki APIs
  CoreSensorsData getCoreSensorData();

  DockIRData getDockIRData();

  CliffData getCliffData();

  CurrentData getCurrentData();

  GpInputData getGpInputData();

  InertiaData getInertiaData();

  ThreeAxisGyroData getRawInertiaData();

  ControllerInfoData getControllerInfoData();

  Battery batteryStatus();

  double getHeading();

  double getAngularVelocity();

  VersionInfo versionInfo();

  WheelJointStates getWheelJointStates(const WheelJointStates& wheelJointStates);

  bool isAlive();

  bool isEnabled();

  bool isShutdown();

  void resetOdometry();

  void setBaseControl(const double& linear, const double& angular);

  void setLed(const std::string& ledNo, const std::string& ledColor);

  void setDigitalOutput(const DigitalOutput& digitalOutput);

  void setExternalPower(const DigitalOutput& digitalOutput);

  void playSoundSequence(const std::string& soundSequence);

  bool setControllerGain(const ControllerInfoData& controllerInfoData);

  bool getControllerGain();

  PoseUpdateData updateOdometry();

  PoseUpdateData updateOdometry(const PoseUpdateData& pose);

  //sigslots callbacks
  void callNewDataEvent();

  void callRosDebug(const std::string& ros_debug);

  void callRosInfo(const std::string& ros_info);

  void callRosWarn(const std::string& ros_warn);

  void callRosError(const std::string& ros_error);

  void callButtonEvent(const kobuki::ButtonEvent& button_event);

  void callBumperEvent(const kobuki::BumperEvent& bumper_event);

  void callCliffEvent(const kobuki::CliffEvent& cliff_event);

  void callWheelEvent(const kobuki::WheelEvent& wheel_event);

  void callPowerEvent(const kobuki::PowerEvent& power_event);

  void callInputEvent(const kobuki::InputEvent& input_event);

  void callRobotEvent(const kobuki::RobotEvent& robot_event);

  void callVersionInfo(const kobuki::VersionInfo& version_info);

  //v8 event callbacks
  static void newDataEvent(uv_async_t *handle);

  static void rosDebug(uv_async_t *handle);

  static void rosInfo(uv_async_t *handle);

  static void rosWarn(uv_async_t *handle);
  
  static void rosError(uv_async_t *handle);

  static void buttonEvent(uv_async_t *handle);

  static void bumperEvent(uv_async_t *handle);

  static void cliffEvent(uv_async_t *handle);

  static void wheelEvent(uv_async_t *handle);

  static void powerEvent(uv_async_t *handle);

  static void inputEvent(uv_async_t *handle);

  static void robotEvent(uv_async_t *handle);

  static void versionInfo(uv_async_t *handle);

  v8::Handle<v8::Promise>  connect(const std::string& eventName);

  void disconnect(const std::string& eventName);
  
  void SetJavaScriptThis(v8::Local<v8::Object> JavaScriptThis) {
    js_this_.Reset(JavaScriptThis);
  }

 private:
  kobuki::Kobuki kobuki;

  ecl::Pose2D<double> pose_ecl;

  std::string sigslots_namespace = "/kobuki";
  
  Nan::Persistent<v8::Object> js_this_;

  //slots name
  ecl::Slot<> slot_stream_data;
  ecl::Slot<const std::string&> slot_ros_debug;
  ecl::Slot<const std::string&> slot_ros_info;
  ecl::Slot<const std::string&> slot_ros_warn;
  ecl::Slot<const std::string&> slot_ros_error;
  ecl::Slot<const kobuki::ButtonEvent&> slot_button_event;
  ecl::Slot<const kobuki::BumperEvent&> slot_bumper_event;
  ecl::Slot<const kobuki::CliffEvent&>  slot_cliff_event;
  ecl::Slot<const kobuki::WheelEvent&>  slot_wheel_event;
  ecl::Slot<const kobuki::PowerEvent&>  slot_power_event;
  ecl::Slot<const kobuki::InputEvent&>  slot_input_event;
  ecl::Slot<const kobuki::RobotEvent&>  slot_robot_event;
  ecl::Slot<const kobuki::VersionInfo&>  slot_version_info;
  ecl::Signal<const kobuki::VersionInfo&>  signal_version_info;

  //uv_async_t name
  uv_async_t async_stream_data;  
  uv_async_t async_button_event;  
  uv_async_t async_bumper_event;  
  uv_async_t async_cliff_event; 
  uv_async_t async_wheel_event;  
  uv_async_t async_power_event;
  uv_async_t async_input_event;
  uv_async_t async_robot_event;
  uv_async_t async_version_info;
  uv_async_t async_ros_debug;
  uv_async_t async_ros_info;
  uv_async_t async_ros_warn;
  uv_async_t async_ros_error;

  //data
  kobuki::ButtonEvent button_event;
  kobuki::BumperEvent bumper_event;
  kobuki::CliffEvent cliff_event;
  kobuki::WheelEvent wheel_event;
  kobuki::PowerEvent power_event;
  kobuki::InputEvent input_event;
  kobuki::RobotEvent robot_event;
  kobuki::VersionInfo *version_info;
  std::string ros_debug;
  std::string ros_info;
  std::string ros_warn;
  std::string ros_error;
};

#endif  // _KOBUKI_MANAGER_H_
