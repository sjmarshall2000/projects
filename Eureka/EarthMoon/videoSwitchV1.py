#Stephen Marshall 6/3/19
#script to allow a switch on pins a,b to swap between two videos
#using pyautogui to send keypresses and output events
#relevant pyautogui: 
#	 press('a'), press('b')
#	'browserback', 'browserforward', 'browserrefresh', 'browserstop'
#	

from time import sleep
from pyautogui import press, typewrite, hotkey

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD) #set labeling convention
a = 11
b = 7
#GPIO.setup(a, GPIO.IN, pull_up_down=GPIO.PUD_UP)	#set as pull-up input
#GPIO.setup(b, GPIO.IN, pull_up_down=GPIO.PUD_UP)	#default to HIGH, 1

GPIO.setup(a, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)	#set as pull-down input
GPIO.setup(b, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)	#default to LOW, 0

#lastState = 'a' #prob useless
justSwitched = True;
print('about to begin loop')
while True:
	if GPIO.input(a) and GPIO.input(b):
		print('ERROR: Both states triggered')
		break			#end program
	if GPIO.input(a): 	#we are on A
		if justSwitched:
			#press A key:
			print('A connected')
			press('a')
			justSwitched = False
		
	elif GPIO.input(b): #we are on B
		if justSwitched:
			#press B key
			print('B connected')
			press('b')
			justSwitched = False;
		
	else: 				#we are transitioning
		if not justSwitched:
			justSwitched = True
	
	
	
	sleep(0.1)


#---- Experimentation: ----
#while True:
#	if GPIO.input(a) and GPIO.input(b):
#		print('both')
#	elif(GPIO.input(b)): #A is grounded, kinda reversed
#		print('state A')
#	elif(GPIO.input(a)): #B is grounded
#		print('state B')
#	
#	sleep(0.25)
