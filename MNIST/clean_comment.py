import os

a=open('td.c','r')
b=open('td2.c','w')

line='a'
while line !=None:
    line=a.readline();
    if '//' in line:
        line=line[:line.find('//')]
    print line 
    b.write(line)

a.close()
b.close()
