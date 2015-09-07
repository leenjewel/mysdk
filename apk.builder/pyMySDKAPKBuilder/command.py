#-*- coding:utf-8 -*-
import subprocess

class CommandUtil:

    @staticmethod
    def run(*command_list, **options) :
        pipe = subprocess.Popen(command_list, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        while True:
            py_out_line = pipe.stdout.readline()
            if py_out_line == '':
                break
            print options.get("out_prefix", "") + py_out_line.strip()
        error = pipe.stderr.read().strip()
        if len(error) :
            return error
        return None


    @staticmethod
    def runYield(*command_list, **options) :
        pipe = subprocess.Popen(command_list, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        while True:
            py_out_line = pipe.stdout.readline()
            if py_out_line == '':
                break
            yield options.get("out_prefix", "") + py_out_line

        error = pipe.stderr.read().strip()
        if len(error) > 0 :
            yield error

