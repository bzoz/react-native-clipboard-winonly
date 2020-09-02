#pragma once

#include "pch.h"

#include "NativeModules.h"

namespace RNWindowsClipboard {
  
  REACT_MODULE(RNCClipboard);

  struct RNCClipboard {
    REACT_METHOD(getString);
    void getString(winrt::Microsoft::ReactNative::ReactPromise<winrt::Microsoft::ReactNative::JSValue> promise) noexcept;
    
    REACT_METHOD(setString);
    void setString(std::string text, winrt::Microsoft::ReactNative::ReactPromise<winrt::Microsoft::ReactNative::JSValue> promise) noexcept;
  };

}
