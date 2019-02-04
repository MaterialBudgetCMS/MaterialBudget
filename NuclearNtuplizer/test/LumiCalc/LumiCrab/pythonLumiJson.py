import sys
#file = open("List_2018B_Sort.txt", 'r')
#file = open("List_2018C_Sort.txt", 'r')
file = open("List_2018D_Sort.txt", 'r')
lines = file.readlines()
file.close()



iflag = 0
irun = 0
icount = 0
LumiJ = 0
sys.stdout.write("{")
for line in lines:
    parts = line.split() # split line into parts
    if len(parts) > 1:
        column1 = parts[0]
        column2 = parts[1]
        icount  = icount+1;
        #columnLength = len(column2)
        #desireValue = column2[columnLength-3]
        if iflag == 0 and irun != column1:
            if LumiJ != 0:
               sys.stdout.write(str(LumiJ - 1)+"]],")
            print ''
            sys.stdout.write("\""+column1+"\": [["+column2+ ", " )
            irun = column1
            jcount = 0
            LumiJ = int(column2) + 1
            for lineJ in lines:
               partsJ = lineJ.split()
               if len(partsJ) > 1:
                  jcount = jcount+1;
                  if column1 == partsJ[0] and jcount > icount:
                      #print partsJ[1], end = ''
                      if LumiJ == int(partsJ[1]):
                         LumiJ = LumiJ + 1
                      else:
                         sys.stdout.write(str(LumiJ - 1)+"],[" + partsJ[1]+ ",")
                         LumiJ = int(partsJ[1])+1
                      iflag = 1
                  else:
                      iflag = 0
if LumiJ != 0:
   sys.stdout.write(str(LumiJ - 1)+"]]")
sys.stdout.write("}")
print ''
