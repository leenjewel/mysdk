#
# Copyright 2015 leenjewel
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

try :
    import fcntl,errno
    LOCK_EX = fcntl.LOCK_EX
    LOCK_NB = fcntl.LOCK_NB
except ImportError:
    fcntl = None
    import win32con
    import win32file
    import pywintypes
    LOCK_EX = win32con.LOCKFILE_EXCLUSIVE_LOCK
    LOCK_NB = win32con.LOCKFILE_FAIL_IMMEDIATELY
    overlapped = pywintypes.OVERLAPPED()

class FileLock(object) :

    highbits = 0xffff0000

    def __init__(self, file_path) :
        self.file_path = file_path
        self.fp = open(file_path, "w")


    def lock(self, not_block = False) :
        if fcntl :
            if not_block :
                try :
                    fcntl.flock(self.fp, LOCK_EX | LOCK_NB)
                except IOError, e :
                    if e.errno == errno.EACCES or e.errno == errno.EAGAIN :
                        return False
                    raise
            else :
                fcntl.flock(self.fp, LOCK_EX)
        else :
            hfile = win32file._get_osfhandle(self.fp.fileno())
            if not_block :
                try :
                    win32file.LockFileEx(hfile, LOCK_EX | LOCK_NB, 0, FileLock.highbits, overlapped)
                except pywintypes.error, e :
                    if e[0] == 33 :
                        return False
                    raise
            else :
                win32file.LockFileEx(hfile, LOCK_EX, 0, FileLock.highbits, overlapped)
        return True


    def unlock(self) :
        if fcntl :
            fcntl.flock(self.fp, fcntl.LOCK_UN)
        else :
            hfile = win32file._get_osfhandle(self.fp.fileno())
            win32file.UnlockFileEx(hfile, 0, FileLock.highbits, overlapped)
        try :
            self.fp.close()
            self.fp = None
        except :
            pass


    def __del__(self) :
        try :
            if self.fp :
                self.fp.close()
        except :
            pass

