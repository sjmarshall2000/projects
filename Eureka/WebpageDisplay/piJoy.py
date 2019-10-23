import RPi.GPIO as GPIO
import pyautogui
import time

pyautogui.FAILSAFE=False

GPIO.setmode(GPIO.BCM)


MODE = 1;
print("Current MODE: ", MODE)
if MODE % 2 == 0:
	print("Landscape Orientation")
else:
	print("Portrait Orientation")
#MODE +1 means rotating the whole machine counter-clockwise
#
# Mode 0 & 2 are Landscape
# Mode 1 & 3 are Portrait
#		↶				↶			↶				↶
#	  	┏━━━━━━━━━━┓	┏━━━━━━━┓	┏━━━━━━━━━━┓	┏━━━━━━━┓
#	  	┃    ┏━━━━┓┃	┃ ┏━━━━┓┃	┃┏━━━━┓ o o┃	┃ ┏━━━━┓┃
#	  	┃[O] ┃  #0┃┃	┃ ┃  #1┃┃	┃┃  #2┃ [O]┃	┃ ┃  #3┃┃
#	  	┃o o ┗━━━━┛┃	┃ ┃    ┃┃	┃┗━━━━┛    ┃	┃ ┃    ┃┃
#	  	┗━━━━━━━━━━┛	┃ ┗━━━━┛┃	┗━━━━━━━━━━┛	┃ ┗━━━━┛┃
#					↺	┃   ⌌ ⌍o┃				↺	┃o⌌ ⌍   ┃
#						┃   ⌎ ⌏o┃					┃o⌎ ⌏   ┃
#						┗━━━━━━━┛					┗━━━━━━━┛
#								 ↺							 ↺

#System to rotate the directional values based on orientation:

#Pins for JoyStick:	Up, 	Right, 	Down, 	Left
directionalPins =   [4, 	3, 		2, 		14]
UP 	= directionalPins[(0 + MODE) % 4]
RIGHT 	= directionalPins[(1 + MODE) % 4]
DOWN 	= directionalPins[(2 + MODE) % 4]
LEFT 	= directionalPins[(3 + MODE) % 4]


GREEN=15
RED=18

pins=[UP,RIGHT,DOWN,LEFT,GREEN,RED]

for pin in pins:
	GPIO.setup(pin,GPIO.IN,pull_up_down=GPIO.PUD_UP)
MaxX,MaxY=pyautogui.size()

#Values for x, dx, ax
x=MaxX/2
lastX=0
MaxDx=200
Dx0=2
dx=0
ax=3
y=MaxY/2
lastY=0
MaxDy=200
Dy0=2
dy=0
ay=3

while True:

	if GPIO.input(GREEN)==0:
		pyautogui.click()
		while GPIO.input(GREEN)==0:
			print("waiting")
	if GPIO.input(RED)==0:
		pyautogui.click(button='right')
	if GPIO.input(UP)==0 or \
	   GPIO.input(DOWN)==0 or \
	   GPIO.input(LEFT)==0 or \
	   GPIO.input(RIGHT)==0 :
		if GPIO.input(LEFT)==0:
			if lastX==-1:
				dx+=ax
			else:
				dx=Dx0
			lastX=-1
			x-=dx
			if dx>MaxDx:
				dx=MaxDx-1
			if x<0:
				x=0
		if GPIO.input(RIGHT)==0:
			if lastX==1:
				dx+=ax
			else:
				dx=Dx0
			lastX=1
			x+=dx
			if dx>MaxDx:
				dx=MaxDx-1
			if x>MaxX:
				x=MaxX-1
		if GPIO.input(UP)==0:
			if lastY==-1:
				dy+=ax
			else:
				dy=Dy0
			lastY=-1
			y-=dy
			if dy>MaxDy:
				dy=MaxDy-1
			if y<0:
				y=0
		if GPIO.input(DOWN)==0:
			if lastY==1:
				dy+=ay
			else:
				dy=Dy0
			lastY=1
			y+=dy
			if dy>MaxDy:
				dy=MaxDy-1
			if y>MaxY:
				y=MaxY-1
		#3/6/19 added linear component for smoothing
		pyautogui.moveTo(x,y,0.1)
