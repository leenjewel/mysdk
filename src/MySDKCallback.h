#ifndef __MYSDK_CALLBACK_H__
#define __MYSDK_CALLBACK_H_

#include <stdlib.h>
#include <string>
#include <MySDKListener.h>

namespace mysdk
{
    class MySDKCallback
    {
        public:
            MySDKCallback(MySDKListener* listener);
            virtual ~MySDKCallback();
            virtual void onSuccess(std::string sdkName, std::string methodName, std::string result);
            virtual void onFail(std::string sdkName, std::string methodName, int errorCode, std::string errorMessage, std::string result);
            virtual void onCancel(std::string sdkName, std::string methodName, std::string result);
            virtual void onPayResult(bool isError, int errorCode, std::string errorMessage, std::string sdkName, std::string productID, std::string orderID, std::string result);

            int handle = 0;
            MySDKCallback *next = NULL;

            static MySDKCallback* getCallback(int handle);
            static int addCallback(MySDKCallback *callback);
            static int cleanCallback(int handle);

        private:
            MySDKListener* _listener;
    };
};

#endif
