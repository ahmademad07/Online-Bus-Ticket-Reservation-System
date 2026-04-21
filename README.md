Bus Ticket Booking System (C)

This is a console-based Bus Ticket Booking System written in C. It allows users to select bus types, choose routes across Bangladesh, book seats, cancel tickets, and print ticket details.

--------------------------------------------------

Features

- Select different bus types:
  1. Non-AC
  2. AC
  3. Sleeper

- Choose routes:
  - From one district to another (within Bangladesh divisions)

- Seat management:
  - View available seats
  - Book seats
  - Cancel bookings

- Ticket system:
  - Store passenger details (name, phone)
  - Track issue time and journey time
  - Print ticket info

- Refund system:
  - 85% refund if cancelled 16+ hours before journey
  - No refund if less than 16 hours

--------------------------------------------------

How It Works

1. Start the program
2. Choose a bus type
3. Select your route (from & to)
4. View available seats
5. Book a seat
6. Print or cancel ticket anytime

--------------------------------------------------

Data Structure Used

- Binary Search Tree (BST)
  Used to store and manage ticket records based on seat number:
  - Fast search
  - Easy insertion
  - Easy deletion

--------------------------------------------------

Seat Layout

- Non-AC: 32 seats (A1–H4)
- AC: 24 seats (A1–H3)
- Sleeper: 12 seats (A1–F2)

--------------------------------------------------

Ticket Prices

- Non-AC: 800
- AC: 1600
- Sleeper: 2000

--------------------------------------------------

Refund Policy

- Cancel 16 hours or more before journey → 85% refund
- Cancel less than 16 hours → No refund


--------------------------------------------------

Notes

- You must select bus type first before doing anything else
- You must select route before booking ticket
- Seat numbers must match exactly (like A1, B2, etc.)
- Data is not saved after program exit (no file handling yet)

--------------------------------------------------

Future Improvements

- Add file storage (save tickets permanently)
- Add login system
- Improve UI (better formatting or graphics)
- Add multiple buses & schedules

--------------------------------------------------

Author

This project was created for learning purposes:
- C programming
- Data structures (BST)
- Real-life system simulation
