# Add your copyright and license header
#
{
  "targets": [
    {
      "target_name": "node-kobuki",
      "sources": [
        "addon.cpp",

        "gen/nan__kobuki_manager.cpp",

        "kobuki_manager.cpp",

      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        ".", 
        "$HOME/kobuki_core/src/ecl_core/ecl_eigen/include/eigen3.1.2"
      ],
      "cflags!": [
        "-fno-exceptions"
      ],
      "cflags": [
        "-std=c++11"
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
      "libraries": [
        "~/kobuki_core/install/lib/libkobuki.so", 
        "~/kobuki_core/install/lib/libecl_time.so", 
        "~/kobuki_core/install/lib/libecl_devices.so", 
        "~/kobuki_core/install/lib/libecl_exceptions.so", 
        "~/kobuki_core/install/lib/libecl_threads.so"
      ],
      "xcode_settings": {
        "OTHER_CFLAGS": [
          "-std=c++11"
        ]
      },
      "conditions": [
        [
          "OS!=\"win\"",
          {
            "cflags+": [
              "-std=c++11"
            ],
            "cflags_c+": [
              "-std=c++11"
            ],
            "cflags_cc+": [
              "-std=c++11"
            ]
          }
        ],
        [
          "OS==\"mac\"",
          {
            "xcode_settings": {
              "OTHER_CPLUSPLUSFLAGS": [
                "-std=c++11",
                "-stdlib=libc++"
              ],
              "OTHER_LDFLAGS": [
                "-stdlib=libc++"
              ],
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              "MACOSX_DEPLOYMENT_TARGET": "10.8"
            }
          }
        ]
      ]
    }
  ]
}
