{
  "Actions": [
    {
      "States": [
        {
          "Image": "headphones"
        },
        {
          "Image": "speakers"
        }
      ],
      "SupportedInMultiActions": false,
      "Icon": "headphones",
      "Name": "Toggle Audio Device",
      "Tooltip": "Switch between two audio devices.",
      "UUID": "com.fredemmott.audiooutputswitch.toggle"
    },
    {
      "SupportedInMultiActions": true,
      "Icon": "active",
      "Name": "Set Audio Device",
      "Tooltip": "Set a specific audio device",
      "UUID": "com.fredemmott.audiooutputswitch.set",
      "States": [
        {
          "Image": "active"
        },
        {
          "Image": "inactive"
        }
      ]
    }
  ],
  "Author": "Fred Emmott",
  "CodePathMac": "sdaudioswitch",
  "CodePathWin": "sdaudioswitch.exe",
  "Description": "Toggle or set the active audio devices.",
  "Name": "Dial Audio Switcher",
  "PropertyInspectorPath": "propertyinspector/index.html",
  "Icon": "headphones",
  "Category": "Audio Devices",
  "CategoryIcon": "glyphicons-basic-140-adjust",
  "Version": "${CMAKE_PROJECT_VERSION}",
  "OS": [
    {
      "Platform": "windows",
      "MinimumVersion": "10"
    },
    {
      "Platform": "mac",
      "MinimumVersion": "${CMAKE_OSX_DEPLOYMENT_TARGET}"
    }
  ],
  "SDKVersion": 2,
  "Software": {
    "MinimumVersion": "4.1"
  }
}
