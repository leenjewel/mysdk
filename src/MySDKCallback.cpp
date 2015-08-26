#include "MySDKCallback.h"

using namespace mysdk;

static MySDKCallback* _head = NULL;

MySDKCallback::MySDKCallback(MySDKListener* listener):
_listener(listener)
{
}

MySDKCallback* MySDKCallback::getCallback(int handle)
{
    MySDKCallback* callback = _head;
    while (callback) {
        if (callback->handle == handle) {
            return callback;
        }
        callback = callback->next;
    }
    return NULL;
}

int MySDKCallback::addCallback(MySDKCallback *callback)
{
    int handle = 1;
    while (MySDKCallback::getCallback(handle)) {
        handle += 1;
    }
    callback->handle = handle;
    callback->next = _head;
    _head = callback;
    return handle;
}

int MySDKCallback::cleanCallback(int handle)
{
    MySDKCallback* last = NULL;
    MySDKCallback* callback = _head;
    while (callback) {
        if (callback->handle == handle) {
            if (last) {
                last->next = callback->next;
                delete callback;
                return handle;
            } else {
                _head = callback->next;
                delete callback;
                return handle;
            }
        }
        last = callback;
        callback = callback->next;
    }
    return 0;
}

MySDKCallback::~MySDKCallback()
{
    if (_listener) {
        delete _listener;
    }
}

void MySDKCallback::onSuccess(std::string sdkName, std::string methodName, std::string result)
{
    if (_listener && _listener->onSuccess) {
        _listener->onSuccess(sdkName, methodName, result);
    }
}

void MySDKCallback::onFail(std::string sdkName, std::string methodName, int errorCode, std::string errorMessage, std::string result)
{
    if (_listener && _listener->onFail) {
        _listener->onFail(sdkName, methodName, errorCode, errorMessage, result);
    }
}

void MySDKCallback::onCancel(std::string sdkName, std::string methodName, std::string result)
{
    if (_listener && _listener->onCancel) {
        _listener->onCancel(sdkName, methodName, result);
    }
}

void MySDKCallback::onPayResult(bool isError, int errorCode, std::string errorMessage, std::string sdkName, std::string productID, std::string orderID, std::string result)
{
    if (_listener && _listener->onPayResult) {
        _listener->onPayResult(isError, errorCode, errorMessage, sdkName, productID, orderID, result);
    }
}

