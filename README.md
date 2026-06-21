# 🚆 Railway Ticket Reservation Waiting List System

## 📌 Case Study 169 — DSA Practical Project 

---

## 📖 Objective

The objective of this project is to develop an automated railway waiting list management system that ensures **fair allocation of seats** when confirmed tickets become available. The system maintains passenger order using a **Queue (FIFO)**, processes cancellations efficiently, and reduces manual intervention in ticket allocation.

---

## 🧠 Why Queue Data Structure?

A **Queue** follows the **First In First Out (FIFO)** principle, which makes it the most suitable data structure for a railway waiting list:

- The passenger who joins the waiting list **first** should receive the **first available seat**.
- This ensures **fairness** and compliance with real railway reservation policies.
- Enqueue (adding to waiting list) and Dequeue (removing from waiting list) both happen in **O(1)** time.

---

## 🗂️ File Structure

```
DSA_Final/
├── railway_reservation.cpp   
└── README.md                  
```

---

## 🏗️ Class Structure

### 1. `Passenger` Class

Stores basic information about each passenger.

| Data Member     | Type     | Description                        |
|-----------------|----------|------------------------------------|
| `passengerId`   | `int`    | Unique ID auto-generated from 101  |
| `passengerName` | `string` | Name of the passenger              |

**Constructors:**
- **Default constructor** — sets `passengerId = 0` and `passengerName = ""`
- **Parameterized constructor** — takes `id` and `name` as arguments

---

### 2. `RailwayReservation` Class

Handles all the booking, cancellation, and display logic.

| Data Member      | Type                | Access    | Description                                 |
|------------------|---------------------|-----------|---------------------------------------------|
| `totalSeats`     | `int`               | `private` | Fixed number of confirmed seats (set to 5)  |
| `confirmedCount` | `int`               | `private` | Tracks how many seats are currently booked  |
| `confirmedList`  | `vector<Passenger>` | `private` | Stores all confirmed passengers             |
| `waitingList`    | `queue<Passenger>`  | `private` | Queue for waiting list passengers (FIFO)    |
| `idCounter`      | `int`               | `private` | Auto-increments to generate passenger IDs   |

**Member Functions:**

| Function               | Return Type | Description                                              |
|------------------------|-------------|----------------------------------------------------------|
| `bookTicket(name)`     | `void`      | Books a confirmed ticket or adds to waiting list queue   |
| `cancelTicket(id)`     | `void`      | Cancels a ticket and auto-upgrades from waiting list     |
| `showConfirmedList()`  | `void`      | Displays all confirmed passengers with seat numbers      |
| `showWaitingList()`    | `void`      | Displays all passengers in the waiting list with position|

---

## ✨ Features

1. **Book Ticket** — If seats are available, passenger gets a confirmed ticket with seat number. If seats are full, passenger is added to the waiting list queue and their WL position is displayed.

2. **Cancel Ticket** — Removes passenger from confirmed list using their Passenger ID. If someone is in the waiting list, the **first person in queue** automatically gets upgraded to confirmed status.

3. **Show Confirmed Passengers** — Displays a list of all currently confirmed passengers along with their seat numbers and IDs.

4. **Show Waiting List** — Displays all passengers in the waiting list in FIFO order with their position numbers. Uses a temporary copy of the queue to iterate without disturbing the original.

5. **Input Validation** — Handles invalid inputs like entering letters instead of numbers, empty passenger names, and negative/zero IDs.

6. **Menu-Driven Interface** — Uses a `do-while` loop with `switch-case` for user interaction.

---

## 🔄 Workflow

```
Passenger Tries to Book
         │
         ▼
  ┌──────────────┐
  │ Seats left?  │
  └──────┬───────┘
         │
    Yes ◄─┤─► No
         │       │
         ▼       ▼
   Add to       Add to
 confirmedList  waitingList
  (vector)      (queue)
```

```
Confirmed Passenger Cancels
         │
         ▼
  Remove from confirmedList
         │
         ▼
  ┌─────────────────────┐
  │ Waiting list empty?  │
  └──────────┬──────────┘
             │
        No ◄─┤─► Yes
             │       │
             ▼       ▼
     Dequeue first   Seat remains
     passenger and   empty
     add to confirmed
```

---

## ⚙️ How to Compile and Run

```bash
# Step 1: Navigate to the project directory
cd DSA_Final

# Step 2: Compile the program
clang++ railway_reservation.cpp -o railway_reservation

# Step 3: Run the program
./railway_reservation
```

---

## 🖥️ Sample Output

```
===========================================
  RAILWAY TICKET RESERVATION SYSTEM (QUEUE)
===========================================
Total Confirmed Seats Available: 5

--------- MAIN MENU ---------
1. Book Ticket
2. Cancel Ticket
3. Show Confirmed Passengers
4. Show Waiting List
5. Exit
Enter your choice: 1
Enter Passenger Name: Rahul Sharma

Ticket Confirmed!
Passenger Id   : 101
Passenger Name : Rahul Sharma
Seat Number    : 1

--------- MAIN MENU ---------
Enter your choice: 1
Enter Passenger Name: Priya Patel

Ticket Confirmed!
Passenger Id   : 102
Passenger Name : Priya Patel
Seat Number    : 2
```

### When all 5 seats are full:

```
Enter your choice: 1
Enter Passenger Name: Neha Verma

Seats are full. Passenger added to Waiting List.
Passenger Id   : 106
Passenger Name : Neha Verma
Waiting List Position : 1
```

### When a confirmed passenger cancels:

```
Enter your choice: 2
Enter Passenger Id to cancel: 103

Cancelling ticket for: Amit Kumar

Seat Vacant! Next passenger from waiting list upgraded.
Passenger Id   : 106
Passenger Name : Neha Verma
Status         : Confirmed
```

---

## 📊 Time Complexity Analysis

| Operation                      | Time Complexity | Explanation                                          |
|-------------------------------|-----------------|------------------------------------------------------|
| Book Ticket (Confirmed)       | O(1)            | `push_back` on vector is amortized O(1)              |
| Book Ticket (Waiting List)    | O(1)            | `push` on queue is O(1)                              |
| Cancel Ticket (Search)        | O(n)            | Linear search through confirmed list                 |
| Cancel Ticket (Erase)         | O(n)            | `erase` on vector shifts elements                    |
| Upgrade from Waiting List     | O(1)            | `front` + `pop` on queue is O(1)                     |
| Show Confirmed List           | O(n)            | Iterates through the entire confirmed list           |
| Show Waiting List             | O(n)            | Copies and iterates through the queue                |

> Where **n** = number of confirmed passengers

---

## 📚 Data Structures Used

| Data Structure       | STL Container        | Used For                        |
|----------------------|----------------------|---------------------------------|
| **Dynamic Array**    | `vector<Passenger>`  | Storing confirmed passengers    |
| **Queue (FIFO)**     | `queue<Passenger>`   | Managing the waiting list       |

---

## 💡 Key Concepts Demonstrated

- **Object Oriented Programming** — Classes (`Passenger`, `RailwayReservation`), constructors, access specifiers (`public`, `private`)
- **Queue (FIFO)** — `push()`, `pop()`, `front()`, `empty()`, `size()`
- **Vector** — `push_back()`, `erase()`, `size()`, index-based access
- **Switch-Case** — Menu-driven program flow
- **Do-While Loop** — Keeps the menu running until user exits
- **Input Validation** — `cin.fail()`, `cin.clear()`, `cin.ignore()`

---

## 🔮 Possible Future Enhancements

- Add file handling to save and load passenger data
- Add train number and date selection
- Add PNR number generation
- Limit maximum waiting list size
- Add search passenger by name feature
- Add multiple trains support

---
