#ifndef __MYSDK_LISTENER_H__
#define __MYSDK_LISTENER_H__

#include <functional>

namespace mysdk
{
    class MySDKListener
    {
        public:
            MySDKListener();

            typedef std::function<void(std::string,std::string,std::string)> MySDKOnSuccessCallback;
            typedef std::function<void(std::string,std::string,int,std::string,std::string)> MySDKOnFailCallback;
            typedef std::function<void(std::string,std::string,std::string)> MySDKOnCancelCallback;
            typedef std::function<void(bool,int,std::string,std::string,std::string,std::string,std::string)> MySDKOnPayResultCallback;

            MySDKOnSuccessCallback onSuccess;
            MySDKOnFailCallback onFail;
            MySDKOnCancelCallback onCancel;
            MySDKOnPayResultCallback onPayResult;

    };
};

#endif
