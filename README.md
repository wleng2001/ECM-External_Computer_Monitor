# External_Computer_Monitor

## Description
-----

It's program, which may show data about computer (frequency, usage of cpu and ram) on the external device. Program for computer is written in python and works on the windows and linux.
Program for monitor is written in arduino ide for nodemcu 1.0, but can edit it for other device, but I want to do version for other devices.

## Instalation
-----
### Linux device
You can clone it in linux devices: 

#### `git clone https://github.com/wleng2001/ECM-External_Computer_Monitor.git ./ECM`

or download as a zip file on the github webpage.

Next you must check, that you have python and psutil library download. You can check it by writting the information in terminal: 

#### `python3 --version` to check if you have python

You should get information similary to that:

#### `Python 3.9.7`

#### `pip list` to check if you have psutil

You should get information similary to that:

####
```
Package            Version 
------------------ ---------
certifi            2022.6.15
charset-normalizer 2.1.0
idna               3.3
pip                22.2.2
psutil             5.9.1
pyserial           3.5
requests           2.28.1
setuptools         57.4.0
urllib3            1.26.9
vcgencmd           0.1.1
```

If you don't have download python you can do it <a href="https://www.python.org/downloads/">here</a> or you can write the text in terminal:

#### `sudo apt install python3`

If you don't have download psutil you can do it by writting the text in terminal: 

#### `sudo pip3 install psutil`

If you don't have download pip you can do it by writting the text in terminal:

#### ``sudo apt install python3-pip

### Windows device

On the windows devices you can download zip file from github and unpack it.
Next you must check, that you have python and psutil library download. You can check it by writting the information in terminal: 

#### `python --version` to check if you have python

You should get information similary to that:

#### `Python 3.9.7`

#### `pip list` to check if you have psutil

You should get information similary to that:

#### 
```
Package            Version 
------------------ ---------
certifi            2022.6.15
charset-normalizer 2.1.0
idna               3.3
pip                22.2.2
psutil             5.9.1
pyserial           3.5
requests           2.28.1
setuptools         57.4.0
urllib3            1.26.9
vcgencmd           0.1.1
```

If you don't have download python you can do it <a href="https://www.python.org/downloads/">here</a>.
If you don't have psutil you can install it by written the text in cmd (you can find cmd by typing "cmd" after press **win** key):
#### `pip3 install psutil`
if you don't have pip you can install it by writing the command in cmd:
#### `curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py`
after download you must typing the information in cmd:
#### `python get-pip.py`

## Usage
-----



