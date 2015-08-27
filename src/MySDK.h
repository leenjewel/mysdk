#ifndef __MYSDK_H__
#define __MYSDK_H__

#include <string>
#include "MySDKLog.h"
#include "MySDKListener.h"

namespace mysdk
{
    class MySDK
    {
        public:
            static bool hasSDK(std::string sdkName);

            static int applySDKMethodAndReturnInt(std::string sdkName, std::string methodName, std::string params);
            static long applySDKMethodAndReturnLong(std::string sdkName, std::string methodName, std::string params);
            static float applySDKMethodAndReturnFloat(std::string sdkName, std::string methodName, std::string params);
            static double applySDKMethodAndReturnDouble(std::string sdkName, std::string methodName, std::string params);
            static bool applySDKMethodAndReturnBoolean(std::string sdkName, std::string methodName, std::string params);
            static std::string applySDKMethodAndReturnString(std::string sdkName, std::string methodName, std::string params);

            static void applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, int callbackHandle);
            static void applySDKMethodWithCallback(std::string sdkName, std::string methodName, std::string params, MySDKListener* listener);

            static void applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, int callbackHandle);
            static void applySDKPay(std::string sdkName, std::string productID, std::string orderID, std::string params, MySDKListener* listener);
    };
};

#endif
