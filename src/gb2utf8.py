'''
Description: GB2312转utf-8
Version: 1.0
Autor: 
Date: 2022-04-27 20:49:05
LastEditors: 
LastEditTime: 2022-04-27 21:09:35
'''
import os
import codecs
import chardet
 
gErrArray = []
 
 
def convert(fileName, filePath, out_enc="utf-8"):
    try:
        content = codecs.open(filePath, 'rb').read()
        # source_encoding = chardet.detect(content)['encoding']
        # 直接设置GB18030编码节省时间
        source_encoding = 'GB18030'
        # print ("fileName:%s \tfileEncoding:%s" %(fileName, source_encoding))
        print("{0:50}{1}".format(fileName, source_encoding))
 
        if source_encoding != None:
            if source_encoding == out_enc:
                return
            content = content.decode(source_encoding).encode(out_enc)
            codecs.open(filePath, 'wb').write(content)
        else:
            gErrArray.append("can not recgonize file encoding %s" % filePath)
    except Exception as err:
        gErrArray.append("%s:%s" % (filePath, err))
 
 
def explore(dir):
    print(
        "\r\n===============================================================")
    print("{0:50}{1}".format('fileName', 'fileEncoding'))
    print("===============================================================")
    for root, dirs, files in os.walk(dir):
        for file in files:
            suffix = os.path.splitext(file)[1]
            if suffix == '.h' or suffix == '.c' or suffix == '.cpp' or suffix == '.hpp' or suffix == '.bat' or suffix == '.java' or suffix == '.txt':
                path = os.path.join(root, file)
                convert(file, path)
 
 
def main():
    #explore(os.getcwd())
    filePath = input("请输入要转换编码的文件夹路径: \n")
    explore(filePath)
    print('\r\n---------错误统计------------')
    for index, item in enumerate(gErrArray):
        print(item)
    print('\r\n共%d个错误！' % (len(gErrArray)))
    if (len(gErrArray) > 0):
        print("请检查错误文件手动修改编码")
    print('\r\n-----------------------------')
 
 
if __name__ == "__main__":
    while True:
        main()
        input("\r\n########### 按回车键继续转换!!! ###########\r\n")