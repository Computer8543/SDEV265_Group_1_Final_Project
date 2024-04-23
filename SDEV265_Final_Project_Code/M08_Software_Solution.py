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
    maximumNumberOfPeopleWhoCanSitInThem: int = 10 # altered from the original C++ coce for simplicity's sake
    numberOfPeopleCurrentlySittingAtTheTable: int = 0
    tableNumber: int = 0
    tableUsage: bool = False
    
        
def welcome_screen(tables: tableType) -> None:
    """ This is the beginning of our application, a menu
        where the user can select from two options, Make Reservation and 
        Check-In Reservation.
    """
    # initalize window
    welcome_screen_gui = tk.Tk()
    
    # create title for window
    welcome_screen_gui.title("Welcome Screen")
    
    # set window size in pixels
    welcome_screen_gui.geometry("720x720")
    
    # prevents you from resizing the welcome screen window
    welcome_screen_gui.resizable(0,0)
    
    # sets the title for the welcome screen 
    welcome_screen_title_label = ttk.Label(welcome_screen_gui, text='Welcome to Messijoes', font=("Times New Roman", 32))
    welcome_screen_title_label.grid(row = 0, column = 3)
    
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
    make_reservation_button = ttk.Button(welcome_screen_gui, text="Make Reservation", command=lambda: make_reservation(tables))
    make_reservation_button.grid(row=1, column=0)
    check_in_reservation_button = ttk.Button(welcome_screen_gui, text="Check-In Reservation", command=lambda: check_in_reservation(tables))
    check_in_reservation_button.grid(row=1, column=5)
    
    # begin welcome screen
    welcome_screen_gui.mainloop()
    
    return 

def make_reservation(tables: tableType) -> None:
    """ make_reservation is the first in a series of functions for the Make Reservation choice 
        on the Welcome Screen Menu. The user enters a name for the reservation, enters the number
        of people in the party (which is input verified) and enters the time for the reservation in
        HH::MM AM/PM. After that, the user clicks Next to go to the confirm_reservation function/page.

    Args:
        reservations (reservationType): A list of reservationType
        tables (tableType): A list of tableType
    """
    
    
    # make name input box variable 
    name_string = tk.StringVar()
    
    # make number of people input box variable
    number_of_people_in_the_party_integer = tk.IntVar()
    
    # make time input box variable
    time_for_the_reservation_string = tk.StringVar()
    
    # initialize window
    make_reservation_gui = tk.Tk()
    
    # Add title for window
    make_reservation_gui.title("Make Reservation Screen")
    
    # set window size in pixels
    make_reservation_gui.geometry("720x720")
    
    # prevents you from resizing the make reservation screen
    make_reservation_gui.resizable(0,0)
    
    # sets the title for the make reservation screen
    make_reservation_title_label = ttk.Label(make_reservation_gui, text='Make Reservation', font=("Times New Roman", 32))
    make_reservation_title_label.grid(row = 0, column = 0)

    # make a label so that the user knows to enter their name in the associated input box
    make_reservation_name_label = ttk.Label(make_reservation_gui, text='Enter a name for the reservation:', font=("Times New Roman", 12))
    make_reservation_name_label.grid(row = 1, column = 0)
    
    # make the name input box
    make_reservation_name_input_window = tk.Frame(make_reservation_gui, width=100, height=50, bd=0, highlightbackground="black", highlightcolor="black", highlightthickness=2)
    make_reservation_name_input_window.grid(row = 1, column = 1)
    
    make_reservation_name_input_field = tk.Entry(make_reservation_name_input_window, font=('times new roman', 12, 'bold'), textvariable=name_string, width=50, bg="#eee", bd=2, justify='left')
    make_reservation_name_input_field.pack() # You need to use the pack function here in order for the input field to work
    make_reservation_name_input_field.focus_set()
    
  
    # make number of people in the party label for the user's sake
    make_reservation_number_of_people_in_the_party_label = ttk.Label(make_reservation_gui, text='Enter the number of people in the party (between 1 and 10 people) in numerical form:', font=("Times New Roman", 12))
    make_reservation_number_of_people_in_the_party_label.grid(row = 3, column = 0)
    
    # make the number of people in the party input box
    make_reservation_number_of_people_in_the_party_input_window = tk.Frame(make_reservation_gui, width=100, height=50, bd=0, highlightbackground="black", highlightcolor="black", highlightthickness=2)
    make_reservation_number_of_people_in_the_party_input_window.grid(row = 3, column = 1)
    
    make_reservation_number_of_people_in_the_party_input_field = tk.Entry(make_reservation_number_of_people_in_the_party_input_window, font=('times new roman', 12, 'bold'), textvariable=number_of_people_in_the_party_integer, width=50, bg="#eee", bd=2, justify='left')

    make_reservation_number_of_people_in_the_party_input_field.pack()
    
    # make time label for the user's sake
    make_reservation_time_label = ttk.Label(make_reservation_gui, text='Enter the time for the reservation in HH::MM AM/PM:', font=("Times New Roman", 12)) 
    make_reservation_time_label.grid(row = 5, column = 0)
    
    # make time input box
    make_reservation_time_input_window = tk.Frame(make_reservation_gui, width=400, height=50, bd=0, highlightbackground="black", highlightcolor="black", highlightthickness=2)
    make_reservation_time_input_window.grid(row = 5, column = 1)
    
    make_reservation_time_input_field = tk.Entry(make_reservation_time_input_window, font=('times new roman', 12, 'bold'), textvariable=time_for_the_reservation_string, width=50, bg="#eee", bd=2, justify='left')
    make_reservation_time_input_field.pack()
    
    # make button to verify contents of make_reservation_number_of_people_in_the_party_input_field and to go to Confirm Reservation Screen
    make_reservation_next_button = ttk.Button(make_reservation_gui, text="Next", command=lambda: make_reservation_bind_tkinter_variables_to_newReservation(tables, name_string, number_of_people_in_the_party_integer, time_for_the_reservation_string))
    make_reservation_next_button.grid(row = 7, column = 0)
    
   
    
    # begin make reservation screen
    make_reservation_gui.mainloop()
    
    return

def make_reservation_bind_tkinter_variables_to_newReservation(tables: tableType, name_string: tk.StringVar, number_of_people_in_the_party_integer: tk.IntVar, time_for_the_reservation_string: tk.StringVar) -> None:
    # add reservation dataclass to store data from tkinter variables
    new_reservation = reservationType(name_string.get() , time_for_the_reservation_string.get(), number_of_people_in_the_party_integer.get(), False)
    
    # pass data to confirm reservation
    confirm_reservation(new_reservation, tables)
    return 
    
def confirm_reservation(new_reservation: reservationType, tables: tableType) -> None:
    pass
    
def check_in_reservation(tables: tableType) -> None:
    pass 

def verify_number_of_people_in_the_party_input_field_in_make_reservation(number_of_people_in_the_party_integer: tk.IntVar) -> bool:
    """ This function verifies that the number of people in the party input field in make reseration 
        has a number between 1 and 10 in it. It returns False if text or a float number
        was entered into the field, and returns False if a number was entered into the field 
        but it was not between 1 and 10. If neither of those cases are true, then it returns True.
    """
    if number_of_people_in_the_party_integer.get() == "":
        return True
    elif type(number_of_people_in_the_party_integer) != tk.IntVar:
        return False
    elif number_of_people_in_the_party_integer.get() < 1 or number_of_people_in_the_party_integer.get() > 10:
        return False
    else:
        return True
def when_invalid() -> None:
    """When the input is invalid, a message is displayed to the user stating that the input is wrong and
       that they should reenter it. 
    """
    when_invalid_gui = tk.Tk()
    when_invalid_gui.title("Error Message")
    when_invalid_gui.geometry("480x480")
    when_invalid_gui.resizable(0,0)
    when_invalid_error_message_text = ttk.Label(when_invalid_gui, text='The inputted value you entered was either not a number, or was not between 1 and 10. Put the number of people in the party in numerical form.', font=("Times New Roman", 12) )
    when_invalid_error_message_text.pack()
    when_invalid_gui.mainloop()
    
# main function 
if __name__ == "__main__": 
    
    """ We intitalize the two main lists of dataclasses here, reservations for the list of 
    reservation dataclasses, and tables for the list of table dataclasses. 
    Then we begin the welcome_screen function for the user.
"""
    tables: tableType = [] 

    welcome_screen(tables)
    
    
