
import os
pwd = os.path.split(os.path.realpath(__file__))[0]
settings = {
    "debug" : True,
    "sdk_search_paths" : [os.path.join(pwd, os.pardir, os.pardir, "android"),],
}
