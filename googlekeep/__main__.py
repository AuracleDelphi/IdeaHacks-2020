from reminders_client import RemindersClient
from datetime import datetime
from time import sleep
import serial
import sys
ser = serial.Serial("COM4")
import itertools
DEADLINE = 2 * 3600
currentFun = True

spinner = itertools.cycle(['-', '/', '|', '\\'])

def main():
    global currentFun
    print(f'Connected to {ser} port')
    client = RemindersClient()
    while True:
        reminders = client.list_reminders(50)
        now = datetime.now()
        faultFound = False
        for remind in reminders:
            if remind is None:
                continue
            delta = (remind.dt - now)
            deltaSec = delta.total_seconds()
            if deltaSec < DEADLINE and deltaSec > 0 and not remind.done:
                if currentFun == True:
                    print("You need to complete:")
                    print(remind)
                    print(f"Due in {delta}")
                nofun()
                faultFound = True
                currentFun = False
                break
        if not faultFound:
            currentFun = True
            fun()
        for _ in range(50):
            sys.stdout.write('\r')
            sys.stdout.write(next(spinner))
            sys.stdout.flush()
            sleep(0.1)

def fun():
    print('*', end='')
    ser.write(b'o')

def nofun():
    print('x', end='')
    ser.write(b'O')

if __name__ == "__main__":
    main();