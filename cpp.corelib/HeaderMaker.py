# -*- coding: utf-8 -*-
import re
import os
import sys

headers = []
basePath = ''

def ReadHeader(fileName):
    if fileName not in headers:
        headers.append(fileName)
        f = open(fileName, 'r')
        txt = f.read()
        f.close()
        return txt
    else:
        raise Exception()

def WriteHeader(fileName, fileTxt):
    f = open(fileName, 'w')
    f.write(fileTxt)
    f.close()

def replaceFunc(txt):
    fileName = txt.group(1)
    fileName = os.path.join(basePath, fileName)
    readTxt = txt.group()
    try:
        readTxt = ReadHeader(fileName)
        readTxt = AnalyseText(readTxt)
    except IOError as e:
        pass
    except Exception as e:
        readTxt = ''
    return readTxt

def AnalyseText(txt):
    return re.sub('#include "(.*)"', replaceFunc, txt)

if __name__ == '__main__':
    fileName = sys.argv[1]
    outputName = sys.argv[2]
    basePath = os.path.dirname(fileName)
    txt = ReadHeader(fileName)
    res = AnalyseText(txt)
    WriteHeader(outputName, res)
