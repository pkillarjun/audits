import os
import sys


def check_banned_api(fname):
    print("'{}'".format(str(fname))) #('"{}"'.format(str1))
    try:
        if len(fname) < 3:
            return
       	os.system('./nas5g_message_decode ' + "'{}'".format(str(fname)))

    except:
        print("[-] Error reading from file " + str(fname))
    return


def get_files(path):
  for root, subdirs, files in os.walk(path):
    for file in os.listdir(root):
        filePath = os.path.join(root, file)
        if os.path.isdir(filePath):
            pass
        else:
            if len(filePath) > 3:
              	check_banned_api(filePath)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        print("Run Analysis !\n")
        get_files(sys.argv[1])
        print("[+] Done")
    else:
        print("program [folder]")

