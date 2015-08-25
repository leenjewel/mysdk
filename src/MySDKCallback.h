#ifndef __MYSDK_CALLBACK_H__
#define __MYSDK_CALLBACK_H_

#include <stdlib.h>
#include <string>

namespace mysdk
{
    class MySDKCallback
    {
        public:
            virtual void onSuccess(std::string sdkName, std::string result);
            virtual void onFail(std::string sdkName, std::string error, std::string result);
            virtual void onCancel(std::string sdkName, std::string result);
            virtual void onPayResult(bool isError, std::string error, std::string sdkName, std::string productID, std::string orderID, std::string result);
            virtual ~MySDKCallback();

            int handle = 0;
            MySDKCallback *next = NULL;

            static MySDKCallback* getCallback(int handle);
            static int addCallback(MySDKCallback *callback);
            static int cleanCallback(int handle);
    };
};

#endif
