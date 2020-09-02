#include "pch.h"
#include "RNWindowsClipboard.h"

using namespace winrt::Windows::ApplicationModel::DataTransfer;

winrt::Windows::Foundation::IAsyncAction GetClipboardData(winrt::Microsoft::ReactNative::ReactPromise<winrt::Microsoft::ReactNative::JSValue> promise) {
  auto captured_promise = promise;
  auto dataPackageView = Clipboard::GetContent();
  if (dataPackageView.Contains(StandardDataFormats::Text())) {
    auto text = co_await dataPackageView.GetTextAsync();
    winrt::Microsoft::ReactNative::JSValue value;
    value = winrt::to_string(text);
    promise.Resolve(value);
  }
  else {
    promise.Resolve("");
  }
}

void RNWindowsClipboard::RNCClipboard::getString(winrt::Microsoft::ReactNative::ReactPromise<winrt::Microsoft::ReactNative::JSValue> promise) noexcept {
  auto asyncOp = GetClipboardData(promise);
  asyncOp.Completed([promise](auto action, auto status) {
    if (status == winrt::Windows::Foundation::AsyncStatus::Error) {
      std::stringstream errorCode;
      errorCode << "0x" << std::hex << action.ErrorCode() << std::endl;
      auto error = winrt::Microsoft::ReactNative::ReactError();
      error.Message = "HRESULT " + errorCode.str() + ": " + std::system_category().message(action.ErrorCode());
      promise.Reject(error);
    }
   });
}

void RNWindowsClipboard::RNCClipboard::setString(std::string text, winrt::Microsoft::ReactNative::ReactPromise<winrt::Microsoft::ReactNative::JSValue> promise) noexcept {
  auto dataPackage = DataPackage();
  dataPackage.SetText(winrt::to_hstring(text));
  if (Clipboard::SetContentWithOptions(dataPackage, nullptr)) {
    winrt::Microsoft::ReactNative::JSValue value;
    promise.Resolve(value);
  } else {
    promise.Reject(winrt::Microsoft::ReactNative::ReactError());
  }
}
