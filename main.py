import threading
import logging
import time


def timer_thread1(name):
    timestamp = time.strftime('%H:%M:%S')
    print(f"{name} (24hr timer) updating. Time: {timestamp}")

    # Call data upload function here


if __name__ == "__main__":
    # Check initialisation code

    # Initialise the 24hr timer
    x = 0
    while x < 5:
        timer1 = threading.Thread(target=timer_thread1, args=["timer1"])
        timer1.start()
        time.sleep(2)
        x = x+1
