#include "MySDKListener.h"

using namespace mysdk;

MySDKListener::MySDKListener():
onSuccess(nullptr),
onFail(nullptr),
onCancel(nullptr),
onPayResult(nullptr)
{
}

