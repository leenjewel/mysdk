/**
 * Copyright 2015 leenjewel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MySDKCallback.h"
#include "MySDKLog.h"

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

MySDKCallback* MySDKCallback::cleanCallback(int handle)
{
    MySDKCallback* last = NULL;
    MySDKCallback* callback = _head;
    while (callback) {
        if (callback->handle == handle) {
            if (last) {
                last->next = callback->next;
                return callback;
            } else {
                _head = callback->next;
                return callback;
            }
        }
        last = callback;
        callback = callback->next;
    }
    return NULL;
}

MySDKCallback::~MySDKCallback()
{
    if (_listener) {
        delete _listener;
    }
}

#define MYSDK_CALL_LISTENER(method,...) \
    if (_listener && _listener->method) {\
        LOGD("MySDKCallback call listener %s", #method);\
        _listener->method(__VA_ARGS__);\
    } else {\
        LOGD("MySDKCallback listener method %s is null", #method);\
    }

void MySDKCallback::onSuccess(std::string sdkName, std::string methodName, std::string result)
{
    MYSDK_CALL_LISTENER(onSuccess, sdkName, methodName, result)
}

void MySDKCallback::onFail(std::string sdkName, std::string methodName, int errorCode, std::string errorMessage, std::string result)
{
    MYSDK_CALL_LISTENER(onFail, sdkName, methodName, errorCode, errorMessage, result)
}

void MySDKCallback::onCancel(std::string sdkName, std::string methodName, std::string result)
{
    MYSDK_CALL_LISTENER(onCancel, sdkName, methodName, result)
}

void MySDKCallback::onPayResult(bool isError, int errorCode, std::string errorMessage, std::string sdkName, std::string productID, std::string orderID, std::string result)
{
    MYSDK_CALL_LISTENER(onPayResult, isError, errorCode, errorMessage, sdkName, productID, orderID, result)
}

