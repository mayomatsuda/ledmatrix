# modules
from nbformat import read
import requests
from datetime import datetime, date
import sys
import time

# store the URL
URL = "http://gtfs.ltconline.ca/TripUpdate/TripUpdates.json"

# get time of bus arrival at specific stop and route
def get_time(route, stop):
    # store the response of URL
    response = requests.get(URL)

    # turn to json
    tx = response.text
    # tx = open("TripUpdates.json").read()

    # lowest occurence of desired route
    ind1_low = tx.find('route_id":"' + route)
    if ind1_low == -1:
        ind1_low = tx.find('route_id": "' + route)

    # next occurence of route id
    ind_between = tx.find('route_id":"', ind1_low + 1)

    # next occurence of desired route
    ind1_high = tx.find('route_id":"' + route, ind1_low + 1)
    if ind1_high == -1:
        ind1_high = tx.find('route_id": "' + route, ind1_low + 1)

    times = []

    while (True):
        
        # this will eventually happen, terminating the loop
        if (ind1_low == -1):
            return sorted(times)

        # ensure instance of the stop exists on the route
        here = tx.find(stop, ind1_low, ind1_high)
        if (here != -1):
            # find occurence of desired stop
            ind2 = tx.find('stop_id":"' + stop, ind1_low)
            if ind2 == -1:
                ind2 = tx.find('stop_id": "' + stop, ind1_low)

            if (ind_between > ind2):
                # find occurence of time at most 50 characters before stop
                ind3 = tx.find('time', ind2 - 50)

                # convert UNIX time to UTC, then to EST
                timeunix = int(tx[ind3+6:ind3+16])
                hour = int(datetime.utcfromtimestamp(timeunix).strftime('%H'))
                if (daylightSavings):
                    hour = str((hour - 4) % 12)
                else:
                    hour = str((hour - 5) % 12)
                if (hour == '0'): hour = '12'
                minute = str(datetime.utcfromtimestamp(timeunix).strftime('%M'))
                time = hour + ":" + minute
                times.append(time)
        
        ind1_low = ind1_high
        ind_between = tx.find('route_id":"', ind1_low + 1)
        ind1_high = tx.find('route_id":"' + route, ind1_low + 1)
        if ind1_high == -1:
            ind1_high = tx.find('route_id": "' + route, ind1_low + 1)

def isDaylightSavings():
    today = date.today()
    m = int(today.strftime("%m"))
    d = int(today.strftime("%d"))

    if (m >= 3 and m <= 11):
        if (m == 3):
            if (d >= 13):
                return True
        elif (m == 11):
            if (d <= 6):
                return True
        else:
            return True

def format_text(route, arr):
    tx = route + ": ;"
    for x in arr:
        tx = tx + x + " "
    tx = tx.rstrip()
    tx = tx + ";"
    return tx

daylightSavings = isDaylightSavings()

route_1 = "02"
route_2 = "102"
stop = "WHARMOIR"

def get_info():
    # Create global variables so they can be updated without interupting the display
    global times_1
    global times_2
    global tx_1
    global tx_2

    times_1 = get_time(route_1, stop)
    times_2 = get_time(route_2, stop)

    tx_1 = format_text(route_1, times_1)
    tx_2 = format_text(route_2, times_2)

    print(tx_1)
    print(tx_2)

get_info()