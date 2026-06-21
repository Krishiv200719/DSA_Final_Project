#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Passenger class to store basic details of a passenger
class Passenger
{
public:
    int passengerId;
    string passengerName;

    Passenger()
    {
        passengerId = 0;
        passengerName = "";
    }

    Passenger(int id, string name)
    {
        passengerId = id;
        passengerName = name;
    }
};

// This class handles all the booking, cancellation and display logic
class RailwayReservation
{
private:
    int totalSeats;
    int confirmedCount;
    vector<Passenger> confirmedList;
    queue<Passenger> waitingList;
    int idCounter; // used to generate passenger id automatically

public:
    RailwayReservation(int seats)
    {
        totalSeats = seats;
        confirmedCount = 0;
        idCounter = 100; // starting passenger id from 100
    }

    // function to book a new ticket
    void bookTicket(string passengerName)
    {
        idCounter = idCounter + 1;
        Passenger p(idCounter, passengerName);

        if (confirmedCount < totalSeats)
        {
            confirmedList.push_back(p);
            confirmedCount++;
            cout << "\nTicket Confirmed!" << endl;
            cout << "Passenger Id   : " << p.passengerId << endl;
            cout << "Passenger Name : " << p.passengerName << endl;
            cout << "Seat Number    : " << confirmedCount << endl;
        }
        else
        {
            waitingList.push(p);
            cout << "\nSeats are full. Passenger added to Waiting List." << endl;
            cout << "Passenger Id   : " << p.passengerId << endl;
            cout << "Passenger Name : " << p.passengerName << endl;
            cout << "Waiting List Position : " << waitingList.size() << endl;
        }
    }

    // function to cancel a confirmed ticket using passenger id
    void cancelTicket(int passengerId)
    {
        bool found = false;
        int index = -1;

        // searching for the passenger in confirmed list
        for (int i = 0; i < confirmedList.size(); i++)
        {
            if (confirmedList[i].passengerId == passengerId)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (found == true)
        {
            cout << "\nCancelling ticket for: " << confirmedList[index].passengerName << endl;
            confirmedList.erase(confirmedList.begin() + index);
            confirmedCount--;

            // check if waiting list queue has someone waiting
            if (!waitingList.empty())
            {
                Passenger nextPassenger = waitingList.front();
                waitingList.pop();
                confirmedList.insert(confirmedList.begin() + index, nextPassenger);
                confirmedCount++;

                cout << "\nSeat Vacant! Next passenger from waiting list upgraded." << endl;
                cout << "Passenger Id   : " << nextPassenger.passengerId << endl;
                cout << "Passenger Name : " << nextPassenger.passengerName << endl;
                cout << "Seat Number    : " << (index + 1) << endl;
                cout << "Status         : Confirmed" << endl;
            }
            else
            {
                cout << "No passenger in waiting list. Seat is now empty." << endl;
            }
        }
        else
        {
            cout << "\nPassenger Id not found in Confirmed List." << endl;
        }
    }

    // function to show all confirmed passengers
    void showConfirmedList()
    {
        cout << "\n----- Confirmed Passenger List -----" << endl;
        if (confirmedList.size() == 0)
        {
            cout << "No confirmed passengers yet." << endl;
        }
        else
        {
            for (int i = 0; i < confirmedList.size(); i++)
            {
                cout << "Seat No: " << (i + 1) << "  Id: " << confirmedList[i].passengerId
                     << "  Name: " << confirmedList[i].passengerName << endl;
            }
        }
        cout << "-------------------------------------" << endl;
    }

    // function to show all passengers currently in waiting list
    void showWaitingList()
    {
        cout << "\n----- Waiting List -----" << endl;
        if (waitingList.empty())
        {
            cout << "Waiting list is empty." << endl;
        }
        else
        {
            queue<Passenger> tempQueue = waitingList; // copy so original queue is not disturbed
            int position = 1;
            while (!tempQueue.empty())
            {
                Passenger p = tempQueue.front();
                tempQueue.pop();
                cout << "WL Position: " << position << "  Id: " << p.passengerId
                     << "  Name: " << p.passengerName << endl;
                position++;
            }
        }
        cout << "-------------------------" << endl;
    }
};

int main()
{
    int totalSeats = 5; // fixed number of confirmed seats for this train
    RailwayReservation railway(totalSeats);

    int choice = 0; // initializing to 0 so it does not hold garbage value
    string name;
    int id;

    cout << "===========================================" << endl;
    cout << "  RAILWAY TICKET RESERVATION SYSTEM (QUEUE) " << endl;
    cout << "===========================================" << endl;
    cout << "Total Confirmed Seats Available: " << totalSeats << endl;

    do
    {
        cout << "\n--------- MAIN MENU ---------" << endl;
        cout << "1. Book Ticket" << endl;
        cout << "2. Cancel Ticket" << endl;
        cout << "3. Show Confirmed Passengers" << endl;
        cout << "4. Show Waiting List" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // checking if the user typed a letter or symbol instead of a number
        if (cin.fail())
        {
            cin.clear();            // clearing the error flag of cin
            cin.ignore(1000, '\n'); // throwing away the bad input from buffer
            cout << "\nInvalid input! Please enter a number between 1 and 5." << endl;
            continue; // go back to the start of the menu loop
        }

        switch (choice)
        {
        case 1:
            cin.ignore(); // clearing leftover newline left behind by cin >> choice
            cout << "Enter Passenger Name: ";
            getline(cin, name);

            // checking if name is empty or made up of only spaces
            bool isBlank;
            isBlank = true;
            for (int i = 0; i < name.length(); i++)
            {
                if (name[i] != ' ')
                {
                    isBlank = false;
                    break;
                }
            }

            if (name.empty() || isBlank == true)
            {
                cout << "\nError: Passenger name cannot be empty! Booking cancelled." << endl;
                break;
            }

            railway.bookTicket(name);
            break;

        case 2:
            cout << "Enter Passenger Id to cancel: ";
            cin >> id;

            // checking if the id entered was not a valid number
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInvalid input! Passenger Id must be a number." << endl;
                break;
            }

            // checking for negative or zero id, since our ids start from 101
            if (id <= 0)
            {
                cout << "\nInvalid Passenger Id! Id cannot be zero or negative." << endl;
                break;
            }

            railway.cancelTicket(id);
            break;

        case 3:
            railway.showConfirmedList();
            break;

        case 4:
            railway.showWaitingList();
            break;

        case 5:
            cout << "\nThank you for using Railway Reservation System!" << endl;
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "\nInvalid choice. Please enter between 1 to 5." << endl;
            break;
        }

    } while (choice != 5);

    return 0;
}