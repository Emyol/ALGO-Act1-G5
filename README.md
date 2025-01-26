```
 █████╗  ██████╗████████╗██╗██╗   ██╗██╗████████╗██╗   ██╗     ██╗
██╔══██╗██╔════╝╚══██╔══╝██║██║   ██║██║╚══██╔══╝╚██╗ ██╔╝    ███║
███████║██║        ██║   ██║██║   ██║██║   ██║    ╚████╔╝     ╚██║
██╔══██║██║        ██║   ██║╚██╗ ██╔╝██║   ██║     ╚██╔╝       ██║
██║  ██║╚██████╗   ██║   ██║ ╚████╔╝ ██║   ██║      ██║        ██║
╚═╝  ╚═╝ ╚═════╝   ╚═╝   ╚═╝  ╚═══╝  ╚═╝   ╚═╝      ╚═╝        ╚═╝                                                
By Group 5, In compliance for Algorithms course CS0007 | FEUTECH                                      
---------------------------------------------------------------------------
```

## 🚀 **Welcome to the Leaderboard and Elevator System Project!**
This repository contains **two systems** that showcase creative and functional programming using custom data structures: a **Leaderboard Management System** and an **Elevator Simulation System**. Both projects highlight key concepts such as **priority queues**, **linked lists**, **file handling**, and **user-friendly GUIs**.

---

### 🎮 **Leaderboard Management System**
A dynamic system for tracking top scores with real-time updates and persistent storage. Features include:

1. **Dynamic Leaderboard**: Automatically adjusts ranks and priorities as new scores are added or updated.
2. **Custom Data Structures**: Uses linked lists and arrays for efficient score management.
3. **Persistent Storage**: Saves and loads data to/from files seamlessly.
4. **Input Validation**: Ensures all user inputs are accurate and error-free.
5. **Interactive Interface**: User-friendly console GUI with clear options.

#### 📝 **How It Works:**
- Players and their scores are stored in a **priority queue**.
- Scores are displayed in a neatly formatted leaderboard.
- Data is saved in `leaderboard.txt` and `record.txt` for persistence.

#### 🌟 **Sample Output:**
```
=========================================
               LEADERBOARD               
=========================================
Rank  1: Alice                   500
Rank  2: Bob                     450
Rank  3: Charlie                 400
=========================================
Press Enter to continue...
```

---

### 🛗 **Elevator Simulation System**
An intelligent system that simulates elevator movement and request handling. Features include:

1. **Custom Priority Queue**: Efficiently handles floor requests based on proximity and direction.
2. **Real-Time Display**: Shows the elevator’s current location, direction, and pending requests.
3. **Dynamic Planning**: Adjusts the queue dynamically for optimized traversal.
4. **Error Handling**: Validates user inputs for floor numbers and directions.

#### 📝 **How It Works:**
- Users request floors, and the elevator plans its path dynamically.
- Uses linked lists to manage requests and track movement.
- Logs elevator activity for troubleshooting and performance review.

#### 🌟 **Sample Output:**
```
+---------------------+
| Elevator Traversal  |
+---------------------+
| Floor | Status      |
+---------------------+
|   9   |             |
|   8   |             |
|   7   |             |
|   6   |     [T]     |
|   5   |             |
|   4   |   [E]       |
|   3   |             |
|   2   |             |
|   1   |             |
+---------------------+
```

---

### 🛠️ **Key Features Across Both Systems**
- **Algorithm Optimization**: Carefully designed to prioritize efficiency and accuracy.
- **File Handling**: Persistent data storage for future use.
- **Interactive Interface**: User-friendly menus and detailed output.
- **Robust Error Handling**: Handles invalid inputs gracefully.

---

### 📂 **Files in This Repository**
- `main.cpp`: The primary codebase for both systems.
- `leaderboard.txt`: Stores the top 10 leaderboard entries.
- `record.txt`: Backup of all player records.
- `Activity1-ELEVATOR.cpp`: File for running the Elevator System.
- `Elevator Path Logs.txt`: Logs of elevator movement and stops.

---

### 🤝 **Contributing**
## **Elevator System Pair**
- Amiel Acuna - Documentation & Quality Assurance
- Sean Viacrusis (Leader) - System Designer & Programmer
## **Leaderboard System Pair**
- Marcus Austria - Documentation & Quality Assurance
- Ferdinand Valentino - System Designer & Programmer



---

```
████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗    ██╗   ██╗ ██████╗ ██╗   ██╗
╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝    ╚██╗ ██╔╝██╔═══██╗██║   ██║
   ██║   ███████║███████║██╔██╗ ██║█████╔╝      ╚████╔╝ ██║   ██║██║   ██║
   ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗       ╚██╔╝  ██║   ██║██║   ██║
   ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗       ██║   ╚██████╔╝╚██████╔╝
   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝       ╚═╝    ╚═════╝  ╚═════╝ 
                                                                          
Thank you for exploring this project!
```

