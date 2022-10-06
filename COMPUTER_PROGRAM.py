port='COM5'
baudrate=115200

from psutil import cpu_percent, cpu_freq, virtual_memory
from serial import *
from time import sleep
from sys import platform

def wskaznik(procent, dlugosc):
    ramka_p='('
    ramka_t=')'
    dlugosc=dlugosc-2
    precent_div_sign=round(100/dlugosc,2)
    wskaznik=ramka_p
    i=precent_div_sign
    while i<100+precent_div_sign:
        if i>100:
            i=100
        if procent>=i:
            wskaznik+="="
        else:
            wskaznik+=" "
        i+=precent_div_sign
    return wskaznik+ramka_t

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



def stojaca_liczba(liczba, max_dlug):
    liczba_ret=''
    i=10
    while i<=max_dlug:
       if i>liczba:
           liczba_ret+=' '
       i*=10    
    return liczba_ret+str(liczba)

def write_cpu_stats(height,width, last_position): #height and width in sign amount
    text=""
    center_h=int(height/3)
    for i in range(0,width*center_h,1):
        text+=(" ")
    if width<18:
        cpu_usage=int(cpu_percent())
        text+="CPU "
        text+=wskaznik(cpu_usage+4, width-4)
    else:
        cpu_usage=int(cpu_percent())
        text+="CPU "+stojaca_liczba(cpu_usage,100)+"% "
        text+=wskaznik(cpu_usage+4, width-9)

    cpu_frequent=round(cpu_freq()[0]/1000, 1)
    cpu_freq_max=round(cpu_freq()[2]/1000, 1)
    if width<18:
        text+="Freq "
        text+=wskaznik(cpu_frequent/cpu_freq_max*100, width-5)
    else:
        text+="CPU "+stojaca_liczba(cpu_frequent,10)+"GHz "
        text+=wskaznik(cpu_frequent/cpu_freq_max*100, width-12)

    if width<18:
        ram_usage=int(virtual_memory()[2])
        text+="RAM "
        text+=wskaznik(ram_usage+4, width-4)
    else:
        ram_usage=int(virtual_memory()[2])
        text+="RAM "+stojaca_liczba(ram_usage,100)+"% "
        text+=wskaznik(ram_usage+4, width-9)

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
        port_n='COM'
        print(f"Windows port name started at \"{port_n}\"")
    elif os=='linux':
        port_n='usb'
        print(f"Linux port name started at \"{port_n}\"")
    else:
        return None
    ser=find_port(port_n, min_port, max_port)
    return ser

def find_port(port_n, min_port, max_port):
    ser=None
    for a_port in range(min_port, max_port):
        print(f"Search port... I'm on the port: {port_n+str(a_port)}")
        if a_port>max_port:
            print("ERROR! Don't find right port in the range.")
            return None
        try:
            ser = Serial(port=port_n+str(a_port), baudrate=baudrate, parity=PARITY_NONE, stopbits=STOPBITS_ONE, bytesize=EIGHTBITS, timeout=2)
        except:
            print(f"Device isn't connected to {port_n+str(a_port)}")
        if ser!=None:
            break
    return ser

ser = port_conf(find_os(), 0, 10)

last_position=0

while True:
    if ser==None:
        print("Device isn't connected")
        break
    text, last_position=write_cpu_stats(4,21, last_position)
    print(text)
    ser.write(str.encode(text))
    sleep(1.1)
