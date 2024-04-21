""" Group: Group 1
    Names: Kyle Ingersoll, Dylan Howard, Vanya Bays
    Date: 4/17/2024
    Summary: This program is a partial remake of the CSCI101 Final Project 
    by Kyle Ingersoll, in Python using Tkinter. 
"""

import tkinter as tk # for the gui mainloop and to be easier to write and read
from tkinter import ttk # for the gui widgets
from PIL import ImageTk, Image # with the default tkinter Photolabel having errors with .jpg images,
                               # this import is needed to fix them
from dataclasses import dataclass # the dataclasses are used to replace the structs in the original
                                  # C++ code

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
    
        
def welcome_screen(reservations: reservationType, tables: tableType) -> None:
    """ This is the beginning of our application, a menu
        where the user can select from two options, Make Reservation and 
        Check-In Reservation.
    """
    # initalize window
    welcome_screen_gui = tk.Tk()
    
    # create title for window
    welcome_screen_gui.title("Welcome to Messijoes")
    
    # set window size in pixels
    welcome_screen_gui.geometry("720x720")
    
    # prevents you from resizing the welcome screen window
    welcome_screen_gui.resizable(0,0)
    
    # sets the title for the welcome screen 
    title_label = ttk.Label(welcome_screen_gui, text='Welcome to Messijoes', font=("Times New Roman", 32))
    title_label.grid(row = 0, column = 3)
    
    # sets up the stock image of an open sign in the welcome screen
    """ Note: tkinter doesn't support .jpg images! Use .png images instead or
        convert .jpg images to .png images.
    """
    photo1 = ImageTk.PhotoImage(Image.open('./Open_Sign_Photo_For_Welcome_Screen.png')) # using ImageTK just in case                                                                              
    photo1_label = ttk.Label(welcome_screen_gui, image=photo1, padding=5)
    photo1_label.grid(row = 5, column = 3)
    
    # set up both make_reservation and check_in_reservation menu buttons in the Welcome Screen
    """ Note: Do not use grid and pack methods with objects that have the same parent in tkinter! 
        It will create an error! Use either all grid or all pack.
    """
    make_reservation_button = ttk.Button(welcome_screen_gui, text="Make Reservation", command=lambda: make_reservation(reservations, tables))
    make_reservation_button.grid(row=1, column=0)
    check_in_reservation_button = ttk.Button(welcome_screen_gui, text="Check-In Reservation", command=lambda: check_in_reservation(reservations, tables))
    check_in_reservation_button.grid(row=1, column=5)
    # begin welcome screen
    welcome_screen_gui.mainloop()
        

def make_reservation(reservations: reservationType, tables: tableType) -> None:
    pass

def check_in_reservation(reservations: reservationType, tables: tableType) -> None:
    pass 

""" We intitalize the two main lists of dataclasses here, reservations for the list of 
    reservation dataclasses, and tables for the list of table dataclasses. 
    Then we begin the welcome_screen function for the user.
"""
reservations: reservationType = []
tables: tableType = [] 

welcome_screen(reservations, tables)
    
    
