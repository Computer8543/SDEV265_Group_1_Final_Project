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
    
        
def welcome_screen(reservations: list[reservationType], tables: list[tableType]) -> None:
    """ This is the beginning of our application, a menu
        where the user can select from two options, Make Reservation and 
        Check-In Reservation.
    """
    # note: use Toplevel windows when you need to call the window function more than once
    # initalize Welcome Screen
    welcome_screen_gui = tk.Toplevel()
    
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
    make_reservation_button = ttk.Button(welcome_screen_gui, text="Make Reservation", command=lambda: make_reservation(tables, reservations) or welcome_screen_gui.quit())
    make_reservation_button.grid(row=1, column=0)
    check_in_reservation_button = ttk.Button(welcome_screen_gui, text="Check-In Reservation", command=lambda: check_in_reservation(tables, reservations) or welcome_screen_gui.quit())
    check_in_reservation_button.grid(row=1, column=5)
    
    # begin welcome screen
    welcome_screen_gui.mainloop()
    
    return 
def verify_number_of_people_in_the_party_input_field_in_make_reservation(number_of_people_in_the_party_integer: tk.IntVar) -> bool:
    """ This function verifies that the number of people in the party input field in make reseration 
        has a number between 1 and 10 in it. It returns False if text or a float number
        was entered into the field, and returns False if a number was entered into the field 
        but it was not between 1 and 10. If neither of those cases are true, then it returns True.
    """
    if number_of_people_in_the_party_integer.get() == 0:
        return True
    elif type(number_of_people_in_the_party_integer.get()) == int:
        return True
    elif number_of_people_in_the_party_integer.get() < 1 or number_of_people_in_the_party_integer.get() > 10:
        return True
    else:
        return True
def when_invalid() -> None:
    """When the input is invalid, a message is displayed to the user stating that the input is wrong and
       that they should reenter it. 
    """
    when_invalid_gui = tk.Toplevel()
    when_invalid_gui.title("Error Message")
    when_invalid_gui.geometry("480x480")
    when_invalid_gui.resizable(0,0)
    when_invalid_error_message_text = ttk.Label(when_invalid_gui, text='The inputted value you entered was either not a number, or was not between 1 and 10. Put the number of people in the party in numerical form.', font=("Times New Roman", 12) )
    when_invalid_error_message_text.pack()
    when_invalid_gui.mainloop()
    
def make_reservation(reservations: list[reservationType], tables: list[tableType]) -> None:
    """ make_reservation is the first in a series of functions for the Make Reservation choice 
        on the Welcome Screen Menu. The user enters a name for the reservation, enters the number
        of people in the party (which is input verified) and enters the time for the reservation in
        HH::MM AM/PM. After that, the user clicks Next to go to the confirm_reservation function/page.

    Args:
        reservations (reservationType): A list of reservationType
        tables (tableType): A list of tableType
    """
    
    # close welcome screen 
    # make name input box variable 
    name_string = tk.StringVar()
    
    # make number of people input box variable
    number_of_people_in_the_party_integer = tk.IntVar()
    
    # make time input box variable
    time_for_the_reservation_string = tk.StringVar()
    
    # initialize window
    make_reservation_gui = tk.Toplevel()
    
    # Add title for window
    make_reservation_gui.title("Make Reservation Screen")
    
    # set window size in pixels
    make_reservation_gui.geometry("720x720")
    
    # prevents you from resizing the make reservation screen
    make_reservation_gui.resizable(0,0)
    
    # note: don't make frames or entry widgets ttk, make them tk, or they won't show up on the screen
    
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
    
    """
     
        # todo: fix other two labels and textboxes below not showing up when this is above them
        # note: it seems like the input validation and number of people in the party code block is the problem with the other labels and input boxes not showing up
        # make reservation number of people in the party input validation validate command and invalid command
        ver = make_reservation_gui.register(verify_number_of_people_in_the_party_input_field_in_make_reservation(number_of_people_in_the_party_integer))
        inv = make_reservation_gui.register(when_invalid())
        validate_command = (ver, '%P')
        invalid_command = (inv)
    """   
   
    make_reservation_number_of_people_in_the_party_label = ttk.Label(make_reservation_gui, text='Enter the number of people in the party (between 1 and 10 people) in numerical form:', font=("Times New Roman", 12))
    make_reservation_number_of_people_in_the_party_label.grid(row = 2, column = 0)
    
    # todo: add input verification here
    # make the number of people in the party input box
    make_reservation_number_of_people_in_the_party_input_window = tk.Frame(make_reservation_gui, width=100, height=50, bd=0, highlightbackground="black", highlightcolor="black", highlightthickness=2)
    make_reservation_number_of_people_in_the_party_input_window.grid(row = 2, column = 1)
    
    
    make_reservation_number_of_people_in_the_party_input_field = tk.Entry(make_reservation_number_of_people_in_the_party_input_window, font=('times new roman', 12, 'bold'), textvariable=number_of_people_in_the_party_integer, width=50, bg="#eee", bd=2, justify='left')
    make_reservation_number_of_people_in_the_party_input_field.pack()
    """ make_reservation_number_of_people_in_the_party_input_field.config(validate="focus", validatecommand=validate_command, invalidcommand=invalid_command)
    """
    # make number of people in the party label for the user's sake
   
    # make time label for the user's sake
    make_reservation_time_label = ttk.Label(make_reservation_gui, text='Enter the time for the reservation in HH::MM AM/PM:', font=("Times New Roman", 12)) 
    make_reservation_time_label.grid(row = 5, column = 0)
    
    # make time input box
    make_reservation_time_input_window = tk.Frame(make_reservation_gui, width=400, height=50, bd=0, highlightbackground="black", highlightcolor="black", highlightthickness=2)
    make_reservation_time_input_window.grid(row = 5, column = 1)
    
    make_reservation_time_input_field = tk.Entry(make_reservation_time_input_window, font=('times new roman', 12, 'bold'), textvariable=time_for_the_reservation_string, width=50, bg="#eee", bd=2, justify='left')
    make_reservation_time_input_field.pack()
    
    # make button to verify contents of make_reservation_number_of_people_in_the_party_input_field and to go to Confirm Reservation Screen
    # note: using get() directly on StringVar() or IntVar() variables doesn't work, you have to use get() on the entry widget itself 
    make_reservation_next_button = ttk.Button(make_reservation_gui, text="Next", command=lambda: make_reservation_bind_tkinter_variables_to_newReservation(reservations, tables, make_reservation_name_input_field.get(),  make_reservation_number_of_people_in_the_party_input_field.get(), make_reservation_time_input_field.get()))
    make_reservation_next_button.grid(row = 7, column = 0)
    
    # begin make reservation screen
    make_reservation_gui.mainloop()
    
    
    return

def make_reservation_bind_tkinter_variables_to_newReservation(reservations: reservationType, tables: tableType, customer_name: str, number_of_people_in_the_party: int, time_for_the_reservation: str) -> None:
    # add reservation dataclass to store data from tkinter variables
    
    new_reservation = reservationType(customer_name, time_for_the_reservation, number_of_people_in_the_party, False)
    
    # pass data to confirm reservation
    confirm_reservation(new_reservation, reservations, tables)
    return 
    
def confirm_reservation(new_reservation: reservationType, reservations: list[reservationType], tables: list[tableType]) -> None:
    """ We allow the user to see what they put for their reservation, and decide whether they say yes, no, or cancel.
        If the user chooses to say yes, they return to welcome screen with the reservation added to the reservations list.
        If the user chooses to say no, they return to make reservation screen to fill in their reservation.
        If the user chooses to cancel the reservation, they return to welcome screen with no reservation added to reservation list.
        
    Args:
        new_reservation (reservationType): The reservation made in the previous screen.
        tables (tableType): the list of tables that are avalible 
    """
    # set up Confirm Reservation screen
    confirm_reservation_gui = tk.Toplevel()
    confirm_reservation_gui.geometry("720x720")
    confirm_reservation_gui.title("Confirm Reservation Screen")
    confirm_reservation_gui.resizable(0,0)
    
    # set up confirm reservation title label
    confirm_reservation_title_label = ttk.Label(confirm_reservation_gui, text='Confirm Reservation', font=("Times New Roman", 32))
    confirm_reservation_title_label.grid(row = 0, column = 0)
    
    # set up confirm reservation please confirm the reservation label
    confirm_reservation_please_confirm_the_reservation_label = ttk.Label(confirm_reservation_gui, text='Please confirm the reservation:', font=("Times New Roman", 12))
    confirm_reservation_please_confirm_the_reservation_label.grid(row = 1, column = 0)
    
    # todo: get new_reservation variables to not be blank, completed
    # set up customer name label
    confirm_reservation_customer_name_label = ttk.Label(confirm_reservation_gui, text='Customer Name: ' + new_reservation.customerName, font=("Times New Roman", 12))
    confirm_reservation_customer_name_label.grid(row = 2, column = 1)
    
    # set up reservation time label
    confirm_reservation_reservation_time_label = ttk.Label(confirm_reservation_gui, text='Reservation Time: ' + new_reservation.time, font=("Times New Roman", 12))
    confirm_reservation_reservation_time_label.grid(row = 3, column = 1)

    # set up number of people in party label 
    confirm_reservation_number_of_people_in_party_label = ttk.Label(confirm_reservation_gui, text='Number of people in party: ' + new_reservation.numberOfPeople, font=("Times New Roman", 12))
    confirm_reservation_number_of_people_in_party_label.grid(row = 4, column = 1)
    
    # set up is this information correct label
    confirm_reservation_is_this_information_correct_label =  ttk.Label(confirm_reservation_gui, text='Is this information correct: ', font=("Times New Roman", 12))
    confirm_reservation_is_this_information_correct_label.grid(row = 5, column = 0)
    
    # set up yes button 
    confirm_reservation_yes_button = tk.Button(confirm_reservation_gui, text='Yes', command=lambda: confirm_reservation_yes_option(new_reservation, reservations, tables))
    confirm_reservation_yes_button.grid(row = 6, column = 1)
    
    # set up cancel button 
    confirm_reservation_cancel_button = tk.Button(confirm_reservation_gui, text='Cancel', command=lambda: confirm_reservation_cancel_option(reservations, tables))
    confirm_reservation_cancel_button.grid(row = 7, column = 0)
    
    # set up no button 
    confirm_reservation_no_button = tk.Button(confirm_reservation_gui, text='No', command=lambda: confirm_reservation_no_option(reservations, tables)) 
    confirm_reservation_no_button.grid(row = 7, column = 1)
    
    # begin confirm reservation screen main loop
    confirm_reservation_gui.mainloop()
    
def confirm_reservation_yes_option(new_reservation: reservationType, reservations: list[reservationType], tables: list[tableType]) -> None:
    """ This function activates when the user presses the Yes button in Confirm Reservation Screen. It saves new_reservation to reservations,
        and then passes those arguments back to the Welcome Screen. 

    Args:
        new_reservation (reservationType): The reservation the customer is currently entering
        reservations (reservationType): The list of reservations that the customer entered
        tables (tableType): the list of tables avalible for the customer
    """
    
    # add new_reseration at the end of the reservations list
    reservations.append(new_reservation)
    
    # return to welcome screen with reservation added to reservations list
    welcome_screen(reservations, tables)
    
    return 

def confirm_reservation_cancel_option(reservations: list[reservationType], tables: list[tableType]) -> None:
    
    # return to welcome screen with no reservation added to reservations list
    welcome_screen(reservations, tables)
    
    return 

def confirm_reservation_no_option(reservations: list[reservationType], tables: list[tableType]) -> None:
    # return to Make Reservation Screen to make new reservation
    make_reservation(reservations, tables)
    
    return 
def check_in_reservation(reservations: list[reservationType], tables: list[tableType]) -> None:
    pass 

# main function 
if __name__ == "__main__": 
    
    """ We intitalize the two main lists of dataclasses here, reservations for the list of 
    reservation dataclasses, and tables for the list of table dataclasses. 
    Then we begin the welcome_screen function for the user.
"""
    # create 20 numbered tables from 1 to 20 that at most 10 people can sit at each table
    tables: tableType = [tableType(0, 10, 0, 1, False), tableType(0, 10, 0, 2, False), tableType(0, 10, 0, 3, False),
                         tableType(0, 10, 0, 4, False), tableType(0, 10, 0, 5, False), tableType(0, 10, 0, 6, False),
                         tableType(0, 10, 0, 7, False), tableType(0, 10, 0, 8, False), tableType(0, 10, 0, 9, False),
                         tableType(0, 10, 0, 10, False), tableType(0, 10, 0, 11, False), tableType(0, 10, 0, 12, False),
                         tableType(0, 10, 0, 13, False), tableType(0, 10, 0, 14, False), tableType(0, 10, 0, 15, False),
                         tableType(0, 10, 0, 16, False), tableType(0, 10, 0, 17, False), tableType(0, 10, 0, 18, False),
                         tableType(0, 10, 0, 19, False), tableType(0, 10, 0, 20, False)
                         ] 
    reservations: reservationType = []
    
    # set up root window to be top level window
    root = tk.Tk()
    root.title("Root Window")
    root.geometry("480x100")
    root_label = ttk.Label(root, text='Do not close this window unless you want to close the application.', font=("Times New Roman", 12))
    root_label.pack()
    root.withdraw()
    
    # open Welcome Screen 
    welcome_screen(reservations, tables)
    
    
