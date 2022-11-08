baudrate=9600
new_baudrate=115200
win_port="COM"
linux_port="/dev/ttyUSB"
date_version="2022-11-08"
repo_name="wleng2001/ECM-External_Computer_Monitor"
## library import---------------------------------------------------------------------------------
from psutil import cpu_percent, cpu_freq, virtual_memory
from serial import *
from time import sleep
from sys import platform
import UPDATE_MODULE

##functions definition----------------------------------------------------------------------------
def pointer(precent, length):
    frame_l='('
    frame_r=')'
    length=length-2
    precent_div_sign=round(100/length,2)
    pointer=frame_l
    i=precent_div_sign
    while i<100+precent_div_sign:
        if i>100:
            i=100
        if precent>=i:
            pointer+="="
        else:
            pointer+=" "
        i+=precent_div_sign
    return pointer+frame_r

##sign, which show, that program work correctly on external device display
def load_sign(width,last_position):
    empty='-'
    busy='>>>'
    text=''
    if_busy_is=False
    for i in range(width-len(busy)+1):
        if last_position==i-1 and if_busy_is==False:
            text+=busy
            last_position=i
            if_busy_is=True
        else:
            text+=empty

    if last_position >= width-len(busy):
        last_position=-1
    
    return text, last_position


##allow to take up the same space by number
def const_number(number, max_lenght):
    ret_number=''
    i=10
    while i<=max_lenght:
       if i>number:
           ret_number+=' '
       i*=10    
    return ret_number+str(number)

def write_cpu_stats(height,width, last_position): #height and width in sign amount
    text=""
    center_h=int(height/3)
    for i in range(0,width*center_h,1):
        text+=(" ")
    if width<18:
        cpu_usage=int(cpu_percent())
        text+="CPU "
        text+=pointer(cpu_usage+4, width-4)
    else:
        cpu_usage=int(cpu_percent())
        text+="CPU "+const_number(cpu_usage,100)+"% "
        text+=pointer(cpu_usage+4, width-9)
    try:
        cpu_frequent=round(cpu_freq()[0]/1000, 1)
        cpu_freq_max=round(cpu_freq()[2]/1000, 1)
        if width<18:
            text+="Freq "
            text+=pointer(cpu_frequent/cpu_freq_max*100, width-5)
        else:
            text+="CPU "+const_number(cpu_frequent,10)+"GHz "
            text+=pointer(cpu_frequent/cpu_freq_max*100, width-12)
    except:
        text+=width*" "
    if width<18:
        ram_usage=int(virtual_memory()[2])
        text+="RAM "
        text+=pointer(ram_usage+4, width-4)
    else:
        ram_usage=int(virtual_memory()[2])
        text+="RAM "+const_number(ram_usage,100)+"% "
        text+=pointer(ram_usage+4, width-9)

    text1, last_position = load_sign(width, last_position)
    text+=text1

    return text, last_position

#find os
def find_os():
    if platform=='win32':
        print('Your os is windows')
        return 'win'
    elif platform=='linux' or platform=='linux2':
        print('Your os is linux')
        return 'linux'
    else:
        print('Your os is OS X')
        return 'OS X'

#com conf
def port_conf(os, min_port, max_port):
    port_n=''
    if os=='win':
        port_n=win_port
        print(f"Windows port name started at \"{port_n}\"")
    elif os=='linux':
        port_n=linux_port
        print(f"Linux port name started at \"{port_n}\"")
    else:
        return None
    ser=find_port(port_n, min_port, max_port)
    return ser

def find_port(port_n, min_port, max_port):
    ser=None
    for a_port in range(min_port, max_port):
        print(f"Search port... I'm on the port: {port_n+str(a_port)}")
        sleep(0.1)
        if a_port>max_port:
            print("ERROR! Don't find right port in the range.")
            return None
        try:
            ser = Serial(port=port_n+str(a_port), baudrate=baudrate, parity=PARITY_NONE, stopbits=STOPBITS_ONE, bytesize=EIGHTBITS, timeout=2)
            ser.write(str.encode("VERSION"))
            version=ser.read_until(expected='\n')[:-2].decode()
            if version=="" or len(version)!=16:
                ser.close()
                print(f"Device isn't connected to {port_n+str(a_port)}")
                ser=None
            else:
                print(f"Version of the device is: {version}")
                ser_text="SERIAL "+str(new_baudrate)
                ser.write(str.encode(ser_text))
                ser.close()
                sleep(1)
                ser = Serial(port=port_n+str(a_port), baudrate=new_baudrate, parity=PARITY_NONE, stopbits=STOPBITS_ONE, bytesize=EIGHTBITS, timeout=2)
                ser.write(str.encode("SM_M"))
                sleep(5)
        except:
            print(f"Device isn't connected to {port_n+str(a_port)}")
        if ser!=None:
            break
    return ser


##-----------------------------------------------------------------------------------------------------------------------------
last_position=0

print("Check version of update module...")
UPDATE_MODULE.update_self()

print("Check app update...")
update_available=UPDATE_MODULE.update_check(date_version, repo_name)
if update_available==None:
    print("You don't have internet connection.")
elif update_available==True:
    print("Update is available!")
    ask=input("Do you want download it now (Y/n): ")
    ask=ask.upper()
    if ask=="Y":
        if_download=UPDATE_MODULE.download_update_repo("https://github.com/"+repo_name, getcwd())
        if if_download==False:
            print("Lost connection file wasn't downloaded")
else:
    print("App is current")

ser = port_conf(find_os(), 0, 10)

while True:
    while True:
        if ser==None:
            print("Device isn't connected")
            break
        text, last_position=write_cpu_stats(7,21, last_position)
        print(text)
        try:
            ser.write(str.encode(text))
            sleep(1.1)
        except:
            print("Connection losted")
            break
    sleep(5)
    print("Try to reconnect...")
    ser = port_conf(find_os(), 0, 10)
