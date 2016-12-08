// Add your copyright and license header

#include "gen/nan__kobuki_manager.h"

void initModule(v8::Local<v8::Object> exports) {
  NanKobukiManager::Init(exports);

}

NODE_MODULE(testAttributes, initModule);
