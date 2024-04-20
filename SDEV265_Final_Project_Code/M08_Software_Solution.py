""" Group: Group 1
    Names: Kyle Ingersoll, Dylan Howard, Vanya Bays
    Date: 4/17/2024
    Summary: This program is a partial remake of the CSCI101 Final Project 
    by Kyle Ingersoll, in Python using Tkinter. 
"""

import tkinter as tk
from tk import *
from dataclasses import dataclass

# global variable to prevent all the reservations from being saved in the same place
reservationCount: int = 0

@dataclass
class reservationType:
    """ This is our reservation dataclass, containing the customer's name, 
        the time they will arrive at the restaurant, the number of people in the reservation, and whether
        the reservation is checked in. 
    """
    customerName: str
    time: str
    numberOfPeople: int = 0
    checkInReservation: bool = False

@dataclass
class tableType:
    """ This is our table dataclass, containing the reservation the table is checked-in to, the maximum amount of 
        people who can sit in the table, the number of people who are sitting at the table, the table number, 
        and whether the table is being used or not.
    """
    reservation: reservationType
    maximumNumberOfPeopleWhoCanSitInThem: int = 0
    numberOfPeopleCurrentlySittingAtTheTable: int = 0
    tableNumber: int = 0
    tableUsage: bool = False
    
class application(tk.Tk):
    def __init__(self) -> None:
        super().__init__()
        """ We intitalize the two main lists of dataclasses here, reservations for the list of 
            reservation dataclasses, and tables for the list of table dataclasses. 
            Then we begin the welcome_screen function for the user.
        """
        self.reservations: reservationType = []
        self.tables: tableType = []
        
        welcome_screen(self.reservations, self.tables)
        
    def welcome_screen(self, reservations: reservationType, tables: tableType) -> None:
        """ This is the beginning of our application, a menu
            where the user can select from two options, Make Reservation and 
            Check-In Reservation.
        """
        # initalize window
        self.welcome_screen_gui = tk.Tk()
        
        # create title for window
        self.welcome_screen_gui.title("Welcome to Messijoes")
        
        # set window size in pixels
        self.welcome_screen_gui.geometry("720x720")
        
        
    
    
    
