# 🚌 Bus Ticket Management System in C

A fully functional console-based Bus Ticket Management System written in C.
This project simulates real-world bus booking operations including seat management, route selection, ticket generation, and cancellation with refund calculation.

---

## 🚀 Features

* 🎟️ Book Bus Tickets
* ❌ Cancel Tickets with Refund System
* 🧾 Print Detailed Ticket
* 🪑 Seat Layout Visualization (Live Status)
* 🗺️ Division & District-Based Route Selection
* 🧠 Efficient Ticket Storage using Binary Search Tree (BST)
* ⏱️ Time-Based Journey Scheduling

---

* Stores ticket records using **seat number as key**
* Supports:

  * Fast insertion
  * Quick search
  * Efficient deletion

---

## 🗺️ Route System

* Supports **8 divisions of Bangladesh**:

  * Dhaka
  * Chittagong
  * Sylhet
  * Rajshahi
  * Khulna
  * Barisal
  * Rangpur
  * Mymensingh

* Each division contains multiple districts

* Dynamic district selection using `districtCount[]`

* Division connectivity handled via adjacency matrix

---

## 💺 Seat Configuration

| Bus Type | Total Seats | Layout          |
| -------- | ----------- | --------------- |
| Non-AC   | 32          | 4 seats per row |
| AC       | 24          | 3 seats per row |
| Sleeper  | 12          | 2 seats per row |

---

## 💰 Ticket Pricing

| Bus Type | Price    |
| -------- | -------- |
| Non-AC   | 800 BDT  |
| AC       | 1600 BDT |
| Sleeper  | 2000 BDT |

---

## 📋 Ticket Information Includes

* Bus Type
* Seat Number
* Passenger Name & Phone
* From & To (Division + District)
* Issue Date & Time
* Journey Date & Time

---

## 📸 Sample Output
```
====== TICKET DETAILS ======
Bus Type       : AC
Seat Number    : A1
Name           : John Doe
Phone          : 0123456789
From           : Dhaka (Gazipur)
To             : Rajshahi (Bogra)
Date Of Issue  : 10-04-2026
Issued At      : 05:30 PM
Date Of Journey: 12-04-2026
Departure Time : 08:00 AM
============================
```
---

## ⚙️ System Workflow

1. Select Bus Type
2. Choose Route (Division → District)
3. View Available Seats
4. Book Ticket
5. Print or Cancel Ticket

---


