/* Program name: main.cpp
*  Author: Kyle Ingersoll
*  Date last updated: 10/1/2023
*  Purpose: This program manages the restaurant operations.
*           It takes reservations, checks customers in when they arrive, manages orders, and calculates and enter payment for customer bills.
*/

#include <iostream> // header file for cin and cout
#include <string> // header file for string data type
#include <iomanip> // header file for setprecision function
#include <cctype> // header file for toupper function

using namespace std; // using standard namespace for simplicity's sake

// initialize enumeration for the menu items
enum menuItems { veggieBurger = 1, hamburger, friedChickenSliders, hamburgerSliders, veggieSliders, haddockSandwich, BLT, fauxBLT, chickenBurrito, falafelWrap, cheesePizza, pepperoniPizza, fauxMeatAndChips, fishAndChips };

// initalize structs for reservations, tables, and orders
struct reservationType
{
    string customerName, time;
    int numberOfPeople = 0;
    bool checkInReservation = false;
};
struct tableType
{
    reservationType reservation;
    int maximumNumberOfPeopleWhoCanSitInThem = 0;
    int numberOfPeopleCurrentlySittingAtTheTable = 0, tableNumber = 0;
    bool tableUsage = false;
    bool tableOrderComplete = false;
};
struct orderType
{
    tableType table;
    menuItems itemsOrderedByCustomersAtTheTable[10];
    int numberofItemsOrdered = 0;
    bool orderIsComplete = false, orderHasBeenPaid = false;
};

// function prototypes
void inputFailure();

// intro screen function prototypes
void welcomeScreen(reservationType reservations[], tableType tables[], orderType orders[], int& reservationCount, int& orderCount);

// 1st option "Make Reservation" function prototypes
struct reservationType makeReservation(reservationType reservations[], tableType tables[], orderType orders[], int& reservationCount, int& orderCount);
string reservationName();
int numberOfPeopleInTheParty();
string reservationTime();
struct reservationType changeReservation(reservationType reservations[], tableType tables[], reservationType newReservation, orderType orders[], int& reservationCount, int& orderCount);
struct reservationType confirmReservation(reservationType reservations[], tableType tables[], reservationType newReservation, orderType orders[], int& reservationCount, int& orderCount);

// 2nd option "Check-In Reservation" function prototype
struct tableType checkInReservation(reservationType reservations[], tableType tables[], orderType orders[], int& tableNumber, int& reservationCount, int& orderCount);

// 3rd option "Enter Order" function prototype
struct orderType enterOrder(reservationType reservations[], tableType tables[], orderType orders[], int& reservationCount, int& orderCount);

// 4th option "Complete Order" function prototype
struct orderType completeOrder(reservationType reservations[], tableType tables[], orderType orders[], int& completeOrderChoice, int& reservationCount, int& orderCount);

// 5th option "Calculate and Pay the Bill" function prototype
struct orderType calculateAndPayTheBill(reservationType reservations[], tableType tables[], orderType orders[], int& completeOrderChoice, int& reservationCount, int& orderCount);


int main()
{
    // initalize arrays
    tableType tables[20];
    reservationType reservations[50];
    orderType orders[50];

    //initalize variables
    int reservationCount = 0;
    int orderCount = 0;

    // declare tables array elements' maximum number of people
    tables[0].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[1].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[2].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[3].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[4].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[5].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[6].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[7].maximumNumberOfPeopleWhoCanSitInThem = 2;
    tables[8].maximumNumberOfPeopleWhoCanSitInThem = 10;
    tables[9].maximumNumberOfPeopleWhoCanSitInThem = 10;
    tables[10].maximumNumberOfPeopleWhoCanSitInThem = 6;
    tables[11].maximumNumberOfPeopleWhoCanSitInThem = 6;
    tables[12].maximumNumberOfPeopleWhoCanSitInThem = 6;
    tables[13].maximumNumberOfPeopleWhoCanSitInThem = 6;
    tables[14].maximumNumberOfPeopleWhoCanSitInThem = 4;
    tables[15].maximumNumberOfPeopleWhoCanSitInThem = 4;
    tables[16].maximumNumberOfPeopleWhoCanSitInThem = 4;
    tables[17].maximumNumberOfPeopleWhoCanSitInThem = 4;
    tables[18].maximumNumberOfPeopleWhoCanSitInThem = 4;
    tables[19].maximumNumberOfPeopleWhoCanSitInThem = 4;

    // declare tables array elements' table numbers
    tables[0].tableNumber = 1;
    tables[1].tableNumber = 2;
    tables[2].tableNumber = 3;
    tables[3].tableNumber = 4;
    tables[4].tableNumber = 5;
    tables[5].tableNumber = 6;
    tables[6].tableNumber = 7;
    tables[7].tableNumber = 8;
    tables[8].tableNumber = 9;
    tables[9].tableNumber = 10;
    tables[10].tableNumber = 11;
    tables[11].tableNumber = 12;
    tables[12].tableNumber = 13;
    tables[13].tableNumber = 14;
    tables[14].tableNumber = 15;
    tables[15].tableNumber = 16;
    tables[16].tableNumber = 17;
    tables[17].tableNumber = 18;
    tables[18].tableNumber = 19;
    tables[19].tableNumber = 20;



    // start welcome screen for the program
    welcomeScreen(reservations, tables, orders, reservationCount, orderCount);

    return 0;

}
// start up initial welcome screen for the program
void inputFailure()
{
    std::cin.clear();
    std::cin.ignore(200, '\n');
    return;
}
// acts as the welcome screen for the user with six choices
void welcomeScreen(reservationType reservations[], tableType tables[], orderType orders[], int& reservationCount, int& orderCount)
{
    //initialize variables and arrays

    int menuChoice = 0;
    int i = 0;
    bool closeRestaurantCheck = false;
    int completeOrderChoice;

    do
    {
        // prompt user for choices
        std::cout << "Welcome to Messijoes" << endl; // need to use std::cout to avoid cout being ambiguous
        std::cout << "1. Make Reservation" << endl;
        std::cout << "2. Check-in Reservation" << endl;
        std::cout << "3. Enter Order" << endl;
        std::cout << "4. Complete Order" << endl;
        std::cout << "5. Calculate and Pay Bill" << endl;

        for (i = 0; i < 50; i++)
        {
            if (reservations[i].checkInReservation == true && orders[i].orderIsComplete == true && orders[i].orderHasBeenPaid == true)
            {
                closeRestaurantCheck = true;
            }

        }
        if (closeRestaurantCheck == true)
        {
            std::cout << "6. Close Restaurant" << endl;
        }
        std::cin >> menuChoice;

        if (!std::cin)
        {
            inputFailure();
            menuChoice = 0;
            std::cout << "Choose an option shown on the screen" << endl;
            continue;
        }
        else if (menuChoice < 1 || menuChoice > 6 || menuChoice > 5 && closeRestaurantCheck == false)
        {
            menuChoice = 0;
            std::cout << "Choose an option shown on the screen" << endl;
            continue;
        }
        else
        {
            break;
        }
    } while (menuChoice < 1 || menuChoice > 6 || menuChoice > 5 && closeRestaurantCheck == false);

    do
    {


        // switch structure to handle menuChoice
        switch (menuChoice)
        {
        case 1:
        {
            // use global variable as index to keep track of the number of reservations so that it wouldn't get reset every time this function was called

            reservations[reservationCount] = makeReservation(reservations, tables, orders, reservationCount, orderCount);

            welcomeScreen(reservations, tables, orders, reservationCount, orderCount);

        }
        case 2:
        {
            int numberOfTable;

            tables[numberOfTable - 1] = checkInReservation(reservations, tables, orders, numberOfTable, reservationCount, orderCount);

            welcomeScreen(reservations, tables, orders, reservationCount, orderCount);

        }
        case 3:
        {


            orders[orderCount] = enterOrder(reservations, tables, orders, reservationCount, orderCount);

            // increase order count by 1
            orderCount++;

            welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
        }
        case 4:
        {


            orders[orderCount - 1] = completeOrder(reservations, tables, orders, completeOrderChoice, reservationCount, orderCount);

            welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
        }
        case 5:
        {
            orders[orderCount - 1] = calculateAndPayTheBill(reservations, tables, orders, completeOrderChoice, reservationCount, orderCount);

            welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
        }
        case 6:
        {
            exit(0);
        }
        default:
        {
            inputFailure();
            menuChoice = 0;
            std::cout << "Choose between options 1 to 6 on the menu." << endl;
        }

        }


    } while (menuChoice < 1 || menuChoice > 6);



}
// prompts user for reservation name
string reservationName()
{
    string reservationName;

    std::cout << "Enter a name for the reservation: ";
    inputFailure(); // needed to actually input data into getline
    getline(std::cin, reservationName);

    return reservationName;
}
// prompts user for number of people in the party
int numberOfPeopleInTheParty()
{
    int numberOfPeopleInTheParty = 0;

    do
    {
        std::cout << "Enter the number of people in the party: ";
        std::cin >> numberOfPeopleInTheParty;

        if (!(std::cin))
        {
            inputFailure();
            numberOfPeopleInTheParty = 0;
            std::cout << "What you entered is not a number" << endl;
            continue;
        }
        else if (numberOfPeopleInTheParty < 1 || numberOfPeopleInTheParty > 10)
        {
            std::cout << "The minimum number of people in the party is 1; the maximum number of people in the party is 10." << endl;
            continue;
        }
        else
        {
            break;
        }
    } while (numberOfPeopleInTheParty < 1 || numberOfPeopleInTheParty > 10);

    return numberOfPeopleInTheParty;
}
// prompts user for reservation time
string reservationTime()
{
    string reservationTime;

    std::cout << "Enter the time for the reservation in HH::MM AM/PM: ";
    inputFailure(); // needed to actually input data into getline
    getline(std::cin, reservationTime);

    return reservationTime;
}
// makes a new reservation for the customer
struct reservationType makeReservation(reservationType reservations[], tableType tables[], orderType orders[], int& reservationCount, int& orderCount)
{
    // define new reservation struct and variables 
    reservationType newReservation;

    newReservation.customerName = reservationName();
    newReservation.numberOfPeople = numberOfPeopleInTheParty();
    newReservation.time = reservationTime();

    // output data for confirmation


    return confirmReservation(reservations, tables, newReservation, orders, reservationCount, orderCount);


}
// change reservation if user requests it 
struct reservationType changeReservation(reservationType reservations[], tableType tables[], reservationType newReservation, orderType orders[], int& reservationCount, int& orderCount)
{
    int reservationChangeOption = 0;

    do
    {
        // prompt user with what they want to change
        std::cout << "What do you want to change?" << endl;
        std::cout << "1. Name" << endl;
        std::cout << "2. Number of People" << endl;
        std::cout << "3. Time" << endl;
        std::cout << "4. Cancel" << endl;
        std::cin >> reservationChangeOption;

        // switch structure to handle the various options
        switch (reservationChangeOption)
        {
        case 1:
        {
            newReservation.customerName = reservationName();
            confirmReservation(reservations, tables, newReservation, orders, reservationCount, orderCount);
            return newReservation;
        }
        case 2:
        {
            newReservation.numberOfPeople = numberOfPeopleInTheParty();
            confirmReservation(reservations, tables, newReservation, orders, reservationCount, orderCount);
            return newReservation;

        }
        case 3:
        {
            newReservation.time = reservationTime();
            confirmReservation(reservations, tables, newReservation, orders, reservationCount, orderCount);
            return newReservation;
        }
        case 4:
        {
            welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
        }
        default:
        {
            inputFailure();
            reservationChangeOption = 0;
            std::cout << "Enter a number between 1 and 4" << endl;
            continue;
        }
        }


    } while (reservationChangeOption < 1 || reservationChangeOption > 4);
}
// prompts user to confirm the reservation and accepts input
struct reservationType confirmReservation(reservationType reservations[], tableType tables[], reservationType newReservation, orderType orders[], int& reservationCount, int& orderCount)
{
    char informationOption;
    int i = 0;

    do
    {
        // prompt user to confirm reservation
        std::cout << "Please confirm the reservation:" << endl;
        std::cout << "Reservation Name: " << newReservation.customerName << endl;
        std::cout << "Reservation Time: " << newReservation.time << endl;
        std::cout << "Number in Party: " << newReservation.numberOfPeople << endl;
        std::cout << "Is this information correct [Y]es, [N]o (make changes), [C]ancel?" << endl;
        std::cin >> informationOption;

        // change letter to upper case
        informationOption = toupper(informationOption);


        // handle user choices
        switch (informationOption)
        {
        case 'Y':
        {
            do
            {
                reservations[reservationCount] = newReservation;
                reservationCount++;
                welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
            } while (reservationCount < 50);
        }
        case 'N':
        {
            return changeReservation(reservations, tables, newReservation, orders, reservationCount, orderCount);
        }
        case 'C':
        {
            welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
        }
        default:
        {
            std::cout << "Invalid input, choose Y, N, or C." << endl;
            continue;
        }
        }
    } while (!(informationOption == 'Y' || informationOption == 'N' || informationOption == 'C'));
}
// displays all reservations that haven't yet checked in and allows you to check in the reservation and assign it to a table.
struct tableType checkInReservation(reservationType reservations[], tableType tables[], orderType orders[], int& tableNumber, int& reservationCount, int& orderCount)
{
    int checkInReservationChoice = 0;
    int i = 0;
    int numberOfActualReservations = 0;

    if (reservations[0].numberOfPeople == 0 && reservations[1].numberOfPeople == 0 && reservations[2].numberOfPeople == 0 && reservations[3].numberOfPeople == 0 && reservations[4].numberOfPeople == 0 && reservations[5].numberOfPeople == 0 && reservations[6].numberOfPeople == 0 && reservations[7].numberOfPeople == 0 && reservations[8].numberOfPeople == 0 && reservations[9].numberOfPeople == 0 && reservations[10].numberOfPeople == 0 && reservations[11].numberOfPeople == 0 && reservations[12].numberOfPeople == 0 && reservations[13].numberOfPeople == 0 && reservations[14].numberOfPeople == 0 && reservations[15].numberOfPeople == 0 && reservations[16].numberOfPeople == 0 && reservations[17].numberOfPeople == 0 && reservations[18].numberOfPeople == 0 && reservations[19].numberOfPeople == 0 && reservations[20].numberOfPeople == 0 && reservations[21].numberOfPeople == 0 && reservations[22].numberOfPeople == 0 && reservations[23].numberOfPeople == 0 && reservations[24].numberOfPeople == 0 && reservations[25].numberOfPeople == 0 && reservations[26].numberOfPeople == 0 && reservations[27].numberOfPeople == 0 && reservations[28].numberOfPeople == 0 && reservations[29].numberOfPeople == 0 && reservations[30].numberOfPeople == 0 && reservations[31].numberOfPeople == 0 && reservations[32].numberOfPeople == 0 && reservations[33].numberOfPeople == 0 && reservations[34].numberOfPeople == 0 && reservations[35].numberOfPeople == 0 && reservations[36].numberOfPeople == 0 && reservations[37].numberOfPeople == 0 && reservations[38].numberOfPeople == 0 && reservations[39].numberOfPeople == 0 && reservations[40].numberOfPeople == 0 && reservations[41].numberOfPeople == 0 && reservations[42].numberOfPeople == 0 && reservations[43].numberOfPeople == 0 && reservations[44].numberOfPeople == 0 && reservations[45].numberOfPeople == 0 && reservations[46].numberOfPeople == 0 && reservations[47].numberOfPeople == 0 && reservations[48].numberOfPeople == 0 && reservations[49].numberOfPeople == 0)
    {
        std::cout << "Choose the reservation to check in." << endl;
        std::cout << "There are no reservations to check in. Please make a reservation first." << endl;
        welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
    }
    else
    {
        do
        {
            std::cout << "Choose the reservation to check in" << endl;


            //check number of actual reservations
            for (i = 0; i < 50; i++)
            {
                if (!(reservations[i].numberOfPeople == 0))
                {
                    numberOfActualReservations++;
                }
                else
                {
                    continue;
                }
            }

            // reset i variable 
            i = 0;
            // output reservation customer name, time, and number of people
            do
            {
                if (reservations[i].checkInReservation == false)
                {
                    std::cout << i + 1 << ": " << reservations[i].customerName << " - " << reservations[i].time << ", " << reservations[i].numberOfPeople << " people" << endl;
                    i++;
                }
                else
                {
                    i++;
                    continue;
                }
            } while (i < numberOfActualReservations);


            std::cin >> checkInReservationChoice;

            // deal with input failure and numbers being chosen that are not in the list
            if (!(std::cin))
            {
                inputFailure();
                checkInReservationChoice = 0;
                std::cout << "What you entered was not a number" << endl;
                std::cout << "Choose a number between 1 and " << (numberOfActualReservations) << endl;
                numberOfActualReservations = 0;
                i = 0;
                continue;
            }
            else if (checkInReservationChoice < 1 || checkInReservationChoice > numberOfActualReservations || checkInReservationChoice > (i + 1))
            {

                std::cout << "Choose a number between 1 and " << (numberOfActualReservations) << endl;
                numberOfActualReservations = 0;
                i = 0;
                continue;
            }
            else
            {
                break;
            }
        } while (checkInReservationChoice < 1 || checkInReservationChoice > numberOfActualReservations || checkInReservationChoice > (i + 1));

        // assign more variables 
        i = 0;
        int assignTableChoice = 0;
        tableType tableChoice;
        int actualMinTableNumber = 0;
        int actualMaxTableNumber = 0;
        int tableNumberCounter = 0;

        do
        {
            std::cout << "Please assign a table:" << endl;
            for (i = 0; i < 20; i++)
            {
                if (reservations[checkInReservationChoice - 1].numberOfPeople <= tables[i].maximumNumberOfPeopleWhoCanSitInThem && tables[i].tableUsage == false)
                {
                    std::cout << i + 1 << ": " << tables[i].maximumNumberOfPeopleWhoCanSitInThem << " people" << endl;
                    tableNumberCounter++;
                    actualMaxTableNumber = i + 1;
                }
                else
                {
                    continue;
                }
            }
            if (tableNumberCounter == 0)
            {
                std::cout << "There are no open tables that will fit the party. Please complete some orders and have the customers pay their bills to free up tables." << endl;
                welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
            }

            actualMinTableNumber = actualMaxTableNumber - tableNumberCounter;

            std::cin >> assignTableChoice;

            // deal with input failure and numbers being chosen that are not in the list
            if (!(std::cin))
            {
                inputFailure();
                assignTableChoice = 0;
                std::cout << "What you entered was not a number" << endl;
                std::cout << "Choose a number shown on the screen" << endl;
                continue;
            }
            else if (assignTableChoice < 1 || assignTableChoice > actualMaxTableNumber || assignTableChoice < actualMinTableNumber || assignTableChoice >(i + 1))
            {
                std::cout << "Choose a number shown on the screen" << endl;
                continue;
            }
            else
            {
                tableChoice.reservation = reservations[checkInReservationChoice - 1];
                tableChoice.numberOfPeopleCurrentlySittingAtTheTable = reservations[checkInReservationChoice - 1].numberOfPeople;
                tableChoice.maximumNumberOfPeopleWhoCanSitInThem = tables[assignTableChoice - 1].maximumNumberOfPeopleWhoCanSitInThem;
                tableChoice.tableUsage = true;
                tableChoice.tableNumber = assignTableChoice;
                reservations[checkInReservationChoice - 1].checkInReservation = true;
                tableChoice.reservation.checkInReservation = true;
                tableNumber = assignTableChoice;

                return tableChoice;
            }


        } while (assignTableChoice < 1 || assignTableChoice > actualMaxTableNumber || assignTableChoice < actualMinTableNumber || assignTableChoice >(i + 1));

    }

}
// Prompts the user to choose the table for the order and then choose the entrees for the number of customers at the table
struct orderType enterOrder(reservationType reservations[], tableType tables[], orderType orders[], int& reservationCount, int& orderCount)
{
    int i = 0;
    int tableForTheOrder = 0;
    orderType newOrder;

    if (tables[0].tableUsage == false && tables[1].tableUsage == false && tables[2].tableUsage == false && tables[3].tableUsage == false && tables[4].tableUsage == false && tables[5].tableUsage == false && tables[6].tableUsage == false && tables[7].tableUsage == false && tables[8].tableUsage == false && tables[9].tableUsage == false && tables[10].tableUsage == false && tables[11].tableUsage == false && tables[12].tableUsage == false && tables[13].tableUsage == false && tables[14].tableUsage == false && tables[15].tableUsage == false && tables[16].tableUsage == false && tables[17].tableUsage == false && tables[18].tableUsage == false && tables[19].tableUsage == false)
    {
        std::cout << "Please choose the table for the order: there are no tables without orders." << endl;
        welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
    }
    else
    {
        // prompt user to choose table for the order
        do
        {
            std::cout << "Please choose the table for the order:" << endl;

            for (i = 0; i < 20; i++)
            {
                if (tables[i].tableUsage == true && tables[i].tableOrderComplete == false)
                {
                    std::cout << tables[i].tableNumber << ": Table " << tables[i].tableNumber << endl;
                }
            }
            std::cin >> tableForTheOrder;

            // deal with input failure and table for the order being more than i + 1 and less than 1.
            if (!(std::cin))
            {
                inputFailure();
                i = 0;
                tableForTheOrder = 0;
                std::cout << "You did not choose a number" << endl;
                std::cout << "Choose a number shown on the screen" << endl;
            }
            else if (tableForTheOrder > i + 1 || tableForTheOrder < 1)
            {
                i = 0;
                tableForTheOrder = 0;
                std::cout << "Choose a number shown on the screen" << endl;
            }
            else
            {
                newOrder.table = tables[tableForTheOrder - 1];
                break;
            }

        } while (tableForTheOrder > i + 1 || tableForTheOrder < 1);


        // reset i variable 
        i = 0;

        // declare input array  
        int entreeNumber[10] = { 0 };
        // prompt user to choose 1 entree each for a customer
        do
        {
            std::cout << "Please choose entree number " << i + 1 << endl;
            std::cout << "1: Veggie Burger" << endl;
            std::cout << "2: Hamburger" << endl;
            std::cout << "3: Fried Chicken Sliders" << endl;
            std::cout << "4: Hamburger Sliders" << endl;
            std::cout << "5: Veggie Sliders" << endl;
            std::cout << "6: Haddock Sandwich" << endl;
            std::cout << "7: BLT" << endl;
            std::cout << "8: Faux BLT" << endl;
            std::cout << "9: Chicken Burrito" << endl;
            std::cout << "10: Falafel Wrap" << endl;
            std::cout << "11: Cheese Pizza" << endl;
            std::cout << "12: Pepperoni Pizza" << endl;
            std::cout << "13: Faux Meat and Chips" << endl;
            std::cout << "14: Fish and Chips" << endl;
            std::cin >> entreeNumber[i];

            // deal with input failure and table for the order being more than i + 1 and less than 1.
            if (!(std::cin))
            {
                inputFailure();
                entreeNumber[i] = 0;
                std::cout << "You did not enter a number" << endl;
                std::cout << "Enter a number between 1 and 14" << endl;
            }
            else if (entreeNumber[i] < 1 || entreeNumber[i] > 14)
            {
                entreeNumber[i] = 0;
                std::cout << "Enter a number between 1 and 14" << endl;
            }
            else
            {
                i++;
                continue;
            }
            ;
        } while (i < tables[tableForTheOrder - 1].reservation.numberOfPeople);

        for (i = 0; i < tables[tableForTheOrder - 1].reservation.numberOfPeople; i++)
        {
            switch (entreeNumber[i])
            {
            case 1:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = veggieBurger;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 2:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = hamburger;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 3:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = friedChickenSliders;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 4:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = hamburgerSliders;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 5:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = veggieSliders;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 6:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = haddockSandwich;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 7:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = BLT;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 8:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = fauxBLT;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 9:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = chickenBurrito;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 10:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = falafelWrap;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 11:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = cheesePizza;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 12:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = pepperoniPizza;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 13:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = fauxMeatAndChips;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            case 14:
            {
                newOrder.itemsOrderedByCustomersAtTheTable[i] = fishAndChips;
                newOrder.numberofItemsOrdered++;
                continue;
            }
            default:
            {
                std::cout << "Please enter a number from 1 to 14" << endl;
                continue;
            }
            }
        }

        // sets up order table 
        orders[orderCount].table.tableNumber = tableForTheOrder;
        orders[orderCount].table = tables[tableForTheOrder - 1];
        newOrder.table = orders[orderCount].table;

        // mark table order as complete
        newOrder.table.tableOrderComplete = true;
        tables[(tableForTheOrder - 1)].tableOrderComplete = true;
        return newOrder;

    }





}
// Marks an order as completed which means it has been delivered to a table and is ready to be paid for.
struct orderType completeOrder(reservationType reservations[], tableType tables[], orderType orders[], int& completeOrderChoice, int& reservationCount, int& orderCount)
{
    // declare variables
    int completeOrderOption = 0;
    orderType completeOrder;
    int i;
    bool orderComplete = false;

    for (i = 0; i < 50; i++)
    {
        if (orders[i].table.tableOrderComplete == true && orders[i].orderIsComplete == false)
        {
            orderComplete = true;
        }
    }

    if (orderComplete == false)
    {
        std::cout << "Choose the order to complete: there are no orders to complete." << endl;
        welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
    }
    else
    {
        // prompt user to choose the order to complete, then handle user choices
        do
        {
            std::cout << "Choose the order to complete:" << endl;

            for (i = 0; i < 20; i++)
            {
                if (tables[i].tableUsage == true && tables[i].tableOrderComplete == true && orders[orderCount - 1].orderIsComplete == false)
                {
                    std::cout << i + 1 << ": Table " << tables[i].tableNumber << endl;
                }
            }

            std::cin >> completeOrderOption;

            if (!(std::cin))
            {
                inputFailure();
                i = 0;
                completeOrderOption = 0;
                std::cout << "You did not choose a number" << endl;
                std::cout << "Choose a number shown on the screen" << endl;
            }
            else if (completeOrderOption > i + 1 || completeOrderOption < 1)
            {
                i = 0;
                completeOrderOption = 0;
                std::cout << "Choose a number shown on the screen" << endl;
            }
            else
            {
                completeOrder = orders[orderCount - 1];
                completeOrder.orderIsComplete = true;
                completeOrderChoice = completeOrderOption;
                return completeOrder;
            }

        } while (completeOrderOption > i + 1 || completeOrderOption < 1);

        // links local user choice variable to formal and actual reference parameter


    }


}
// the function calculates and pays the bill
struct orderType calculateAndPayTheBill(reservationType reservations[], tableType tables[], orderType orders[], int& completeOrderChoice, int& reservationCount, int& orderCount)
{
    // declare variables 
    char payBillOption;
    orderType calculateAndPayBill;
    bool orderComplete = false;


    // declare menu item price variables 
    const double veggieBurgerPrice = 35.00;
    const double hamburgerPrice = 45.00;
    const double friedChickenSlidersPrice = 38.00;
    const double hamburgerSlidersPrice = 38.00;
    const double veggieSlidersPrice = 38.00;
    const double haddockSandwichPrice = 38.00;
    const double BLTPrice = 42.00;
    const double fauxBLTPrice = 42.00;
    const double chickenBurritoPrice = 42.00;
    const double falafelWrapPrice = 42.00;
    const double cheesePizzaPrice = 59.00;
    const double pepperoniPizzaPrice = 59.00;
    const double fauxMeatAndChipsPrice = 77.00;
    const double fishAndChipsPrice = 77.00;

    // declare menu subtotal, tip, tax, and final total    
    double subTotal = 0, tip = 0, tax = 0, finalTotal = 0;

    // check all orders to see if order is completed
    for (int i = 0; i < 50; i++)
    {
        if (orders[i].orderIsComplete == true && orders[i].orderHasBeenPaid == false)
        {
            orderComplete = true;
        }
    }

    if (orderComplete == false)
    {
        cout << "Choose the order to calculate the bill: There are no orders ready for payment" << endl;
        welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
    }
    else
    {
        do
        {
            // prompt user for bill
            std::cout << "Here is the bill for table " << orders[orderCount - 1].table.tableNumber << endl;

            // output bill items
            for (int i = 0; i < orders[orderCount - 1].numberofItemsOrdered; i++)
            {
                switch (orders[orderCount - 1].itemsOrderedByCustomersAtTheTable[i])
                {
                case veggieBurger:
                {
                    std::cout << "Veggie Burger - $35.00" << endl;
                    subTotal += veggieBurgerPrice;
                    continue;
                }
                case hamburger:
                {
                    std::cout << "Hamburger - $45.00" << endl;
                    subTotal += hamburgerPrice;
                    continue;
                }
                case friedChickenSliders:
                {
                    std::cout << "Fried Chicken Sliders - $38.00" << endl;
                    subTotal += friedChickenSlidersPrice;
                    continue;
                }
                case hamburgerSliders:
                {
                    std::cout << "Hamburger Sliders - $38.00" << endl;
                    subTotal += hamburgerSlidersPrice;
                    continue;
                }
                case veggieSliders:
                {
                    std::cout << "Veggie Sliders - $38.00" << endl;
                    subTotal += veggieSlidersPrice;
                    continue;
                }
                case haddockSandwich:
                {
                    std::cout << "Haddock Sandwich - $38.00" << endl;
                    subTotal += haddockSandwichPrice;
                    continue;
                }
                case BLT:
                {
                    std::cout << "BLT - $42.00" << endl;
                    subTotal += BLTPrice;
                    continue;
                }
                case fauxBLT:
                {
                    std::cout << "Faux BLT - $42.00" << endl;
                    subTotal += fauxBLTPrice;
                    continue;
                }
                case chickenBurrito:
                {
                    std::cout << "Chicken Burrito - $42.00" << endl;
                    subTotal += chickenBurritoPrice;
                    continue;
                }
                case falafelWrap:
                {
                    std::cout << "Falafel Wrap - $42.00" << endl;
                    subTotal += falafelWrapPrice;
                    continue;
                }
                case cheesePizza:
                {
                    std::cout << "Cheese Pizza - $59.00" << endl;
                    subTotal += cheesePizzaPrice;
                    continue;
                }
                case pepperoniPizza:
                {
                    std::cout << "Pepperoni Pizza - $59.00" << endl;
                    subTotal += pepperoniPizzaPrice;
                    continue;
                }
                case fauxMeatAndChips:
                {
                    std::cout << "Faux Meat and Chips - $77.00" << endl;
                    subTotal += fauxMeatAndChipsPrice;
                    continue;
                }
                case fishAndChips:
                {
                    std::cout << "Fish and Chips - $77.00" << endl;
                    subTotal += fishAndChipsPrice;
                    continue;
                }
                }
            }

            // calculate tip, tax, and final total
            tip = (subTotal / 5);
            tax = (subTotal / 10);
            finalTotal = subTotal + tip + tax;

            // then output subtotal, tip, tax, and final total to the console
            std::cout << fixed << setprecision << setprecision(2);
            std::cout << "Subtotal: $" << subTotal << endl;
            std::cout << "Tip: $" << tip << endl;
            std::cout << "Tax: $" << tax << endl;
            std::cout << "Total: $" << finalTotal << endl;

            // prompt the user to pay bill
            std::cout << "Pay Bill?";
            std::cin >> payBillOption;
            std::cout << endl;
            payBillOption = tolower(payBillOption);

            // switch structure to handle bill payment choice
            switch (payBillOption)
            {
            case 'y':
            {
                calculateAndPayBill = orders[orderCount - 1];
                calculateAndPayBill.orderHasBeenPaid = true;
                return calculateAndPayBill;
            }
            case 'n':
            {
                welcomeScreen(reservations, tables, orders, reservationCount, orderCount);
            }
            default:
            {
                std::cout << "Enter either y or n. Please Try again." << endl;
                continue;
            }
            }



        } while (!(payBillOption == 'y' || payBillOption == 'n'));
    }
}