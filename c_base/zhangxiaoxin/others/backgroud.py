#!/usr/bin/env python
#coding=utf-8
import glob, os
import shutil
import time
import Image

filelist=[]
def filelie(path):
    if os.path.isfile(path):
       wenjian=os.path.splitext(path)[1][1:]
       if wenjian=="jpg" or wenjian=="png" or wenjian=="gif":
        try:
          kuan,gao = Image.open(path).size
          if kuan>=1024 and gao>=768:
            filelist.append(path)
        except IOError:
         pass
    elif os.path.isdir(path):
        for item in os.listdir(path):
            itemsrc = os.path.join(path, item)
            filelie(itemsrc)

curdir = os.getcwd()
filelie(curdir)
currentImageFiles = filelist
#print filelist
if os.path.isfile('backgroundslide.xml'):
 os.remove('backgroundslide.xml')


currentTime = time.localtime()
length = len(currentImageFiles)

f = file('backgroundslide.xml', 'w')

f.write('<background>\n')
f.write('\t<starttime>\n')
f.write('\t\t<year>' + str(currentTime.tm_year) + '</year>\n')
f.write('\t\t<month>' + str(currentTime.tm_mon) + '</month>\n')
f.write('\t\t<day>' + str(currentTime.tm_mday) + '</day>\n')
f.write('\t\t<hour>' + str(currentTime.tm_hour) + '</hour>\n')
f.write('\t\t<minute>' + str(currentTime.tm_min) + '</minute>\n')
f.write('\t\t<second>' + str(currentTime.tm_sec) + '</second>\n')
f.write('\t</starttime>\n')
f.write('<!--This animation will start at the time it created-->\n')

for i in currentImageFiles:
 length = length - 1
 f.write('\t<static>\n')
 f.write('\t\t<duration>2.0</duration>\n')
 f.write('\t\t<file>' + currentImageFiles[length] +'</file>\n')
 f.write('\t</static>\n')
 f.write('\t<transition>\n')
 f.write('\t\t<duration>1.0</duration>\n')
 f.write('\t\t<from>' + currentImageFiles[length] + '</from>\n')
 if length >= 1:
  f.write('\t\t<to>' + currentImageFiles[length-1] + '</to>\n')
 if length <1:
  f.write('\t\t<to>' + currentImageFiles[len(currentImageFiles)-1] + '</to>\n')
 f.write('\t</transition>\n')

f.write('</background>\n')
f.close()
