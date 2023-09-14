# source /apps/root/PRO/setroot_CUE.csh

# line="480: 804925838(10)"
# info=line.split()
# print(info)

# info_data=info[1].split("(")
# print(info_data)

# info_data[1]=info_data[1].replace(')','')
# print(info_data)
# print(info_data[0])
# print(info_data[1])
# print(info_data[0].isdigit())
# print(info_data[1].isdigit())

# string1=bin(int(info_data[1]))
# string2=bin(int(info_data[0]))
# print(string1)
# print(string2)
# print(int(info_data[1]))
# print(int(info_data[0]))

# data = (int(info_data[1])<<32)|int(info_data[0])
# print(bin(data))
# print(data)
# print(float(data))

# icount=0
# for i in range(0,10):
#     # print(i)
#     icount+=1
# print(icount)

# a=[0.0]*10
# print(a)
# a=[10.0]*10
# file = open('Pedestals.txt','w')
# file.write(str(a[2]/2)+'\n')
# file.write(str(a[5]/2)+'\n')
# file.close()

# with open('Pedestals.txt','r') as file_Pedestals:
#     count_Pedestals=0
#     for line in file_Pedestals:
#         count_Pedestals+=1
#         if count_Pedestals<=1080: print(float(line))