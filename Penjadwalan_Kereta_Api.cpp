#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cmath>

// Function Prototypes
int jeda();
int menu();

// Error Handling
bool isInteger(const std::string& str);
bool isFloat(const std::string& str);
// CRUD
void displaySchedule(const struct DayNode* day);
    // Single Linked List
void advanceToNextDay();
        // Queue    
void initializeWeekQueue();
void addTrainSchedule(int trainID, const std::string& destination, const std::string& trainName, int hour);
void enqueueDay(const std::string& day);
void enqueueTrain(struct DayNode* day, int trainID, const std::string& destination, const std::string& trainName, int hour);
void deleteTrainSchedule();
void displayTodaySchedule();
        // Stack
void updateTrainSchedule(int trainID, int newHour);
// Sort
void quickSort();
void mergeSort();
// Search
void fibonacciSearchByTrainID(int trainID);
void jumpSearchByDeparture(int hour);
void boyerMooreSearchByName(const std::string& trainName);

// Define Node structure for single linked list
struct Node {
    int trainID;
    std::string destination;
    std::string trainName;
    int hour;
    Node* next;

    Node(int id, const std::string& dest, const std::string& name, int h)
        : trainID(id), destination(dest), trainName(name), hour(h), next(nullptr) {}
};

// Node for the week queue
struct DayNode {
    std::string dayName;
    Node* head;
    DayNode* next;

    DayNode(const std::string& day) : dayName(day), head(nullptr), next(nullptr) {}
};

// Global head pointer for week queue
DayNode* weekQueueHead = nullptr;

// Main Function
int main() {
    int choice;
    int trainID;
    std::string destination;
    std::string trainName;
    int hour;
    int newHour;
    std::string input;

    while ((choice = menu()) != 0) {
        switch (choice) {
            case 1:
                initializeWeekQueue();
                break;
            case 2:
                std::cout << "Enter Train ID: ";
                std::cin >> input;
                while (!isInteger(input)) {
                    std::cout << "Invalid input. Please enter an integer for Train ID: ";
                    std::cin >> input;
                }
                trainID = std::stoi(input);

                std::cout << "Enter Destination: ";
                std::cin >> destination;

                std::cout << "Enter Train Name: ";
                std::cin >> trainName;

                std::cout << "Enter Departure Hour (in 9 to 5 format): ";
                std::cin >> input;
                while (!isInteger(input) || std::stoi(input) < 900 || std::stoi(input) > 1700 || std::stoi(input) % 100 >= 60) {
                    std::cout << "Invalid input. Please enter a valid hour in 9 to 5 format: ";
                    std::cin >> input;
                }
                hour = std::stoi(input);

                addTrainSchedule(trainID, destination, trainName, hour);
                break;

            case 3:
                std::cout << "Enter Train ID to Update: ";
                std::cin >> input;
                while (!isInteger(input)) {
                    std::cout << "Invalid input. Please enter an integer for Train ID: ";
                    std::cin >> input;
                }
                trainID = std::stoi(input);

                std::cout << "Enter New Departure Hour (in 9 to 5 format): ";
                std::cin >> input;
                while (!isInteger(input) || std::stoi(input) < 900 || std::stoi(input) > 1700 || std::stoi(input) % 100 >= 60) {
                    std::cout << "Invalid input. Please enter a valid hour in 9 to 5 format: ";
                    std::cin >> input;
                }
                newHour = std::stoi(input);

                updateTrainSchedule(trainID, newHour);
                break;

            case 4:
                deleteTrainSchedule();
                break;

            case 5:
                displayTodaySchedule();
                break;

            case 6:
                advanceToNextDay();
                break;

            case 7:
                quickSort();
                break;

            case 8:
                mergeSort();
                break;

            case 9:
                std::cout << "Enter Train ID to Search: ";
                std::cin >> input;
                while (!isInteger(input)) {
                    std::cout << "Invalid input. Please enter an integer for Train ID: ";
                    std::cin >> input;
                }
                trainID = std::stoi(input);

                fibonacciSearchByTrainID(trainID);
                break;

            case 10:
                std::cout << "Enter Departure Hour to Search: ";
                std::cin >> input;
                while (!isInteger(input) || std::stoi(input) < 900 || std::stoi(input) > 1700 || std::stoi(input) % 100 >= 60) {
                    std::cout << "Invalid input. Please enter a valid hour in 9 to 5 Operasional time: ";
                    std::cin >> input;
                }
                hour = std::stoi(input);

                jumpSearchByDeparture(hour);
                break;

            case 11:
                std::cout << "Enter Train Name to Search: ";
                std::cin >> trainName;
                boyerMooreSearchByName(trainName);
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

        jeda();
    }
    return 0;
}

int jeda() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}

bool isInteger(const std::string& str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool isFloat(const std::string& str) {
    bool decimalFound = false;
    for (char const &c : str) {
        if (c == '.') {
            if (decimalFound) return false;
            decimalFound = true;
        } else if (std::isdigit(c) == 0) return false;
    }
    return true;
}

int menu() {
    // system("cls");   // Windows OS
    system("clear");   // Linux OS
    int pilihan;
    std::cout << "===================================" << std::endl;
    std::cout << "= Train Station Scheduling System =" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "[1] Initialize Week Queue          " << std::endl; // dika
    std::cout << "[2] Add Train Schedule             " << std::endl; // dika
    std::cout << "[3] Update Train Schedule          " << std::endl; // kiki
    std::cout << "[4] Delete Train Schedule          " << std::endl; // dika
    std::cout << "[5] Display Today's Schedule       " << std::endl; // dika
    std::cout << "[6] Advance to Next Day            " << std::endl; // dika
    std::cout << "[7] Sort by Train Departure                     " << std::endl; // rava
    std::cout << "[8] Sort by Train Name                     " << std::endl; // rava
    std::cout << "[9] Search by Train Id               " << std::endl; // rava
    std::cout << "[10] Search by Train Departure                   " << std::endl; // kiki
    std::cout << "[11] Search by Train Name            " << std::endl; // kiki
    std::cout << "[0] Exit                           " << std::endl;
    std::cout << "Enter choice: ";
    std::cin >> pilihan;
    return pilihan;
}

int countTrainsInDay(DayNode* day) {
    int count = 0;
    Node* temp = day->head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to add days to the week queue (linked list)
void enqueueDay(const std::string& day) {
    DayNode* newDay = new DayNode(day);
    if (weekQueueHead == nullptr) {
        weekQueueHead = newDay;
        std::cout << "New Week Has Been Initialized " << std::endl;
        jeda();
    } else {
        DayNode* temp = weekQueueHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newDay;
    }
}

// Initialize the week queue with the day name
void initializeWeekQueue() {
    const char* days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; ++i) {
        enqueueDay(days[i]);
    }
}

// Enqueue (add to the end of the list) a train schedule
void enqueueTrain(DayNode* day, int trainID, const std::string& destination, const std::string& trainName, int hour) {
    if (countTrainsInDay(day) >= 5) {
        std::cout << "Cannot add more trains for " << day->dayName << ". Maximum of 5 trains reached.\n";
        return;
    }
    Node* current = day->head;
    while (current != nullptr) {
        if (current->trainID == trainID) {
            std::cout << "Train ID " << trainID << " already exists in today's schedule. Cannot add duplicate.\n";
            return;
        }
        if (current->hour == hour) {
            std::cout << "A train is already scheduled to depart at " << hour << ". Cannot add another train at the same hour.\n";
            return;
        }
        current = current->next;
    }

    Node* newNode = new Node(trainID, destination, trainName, hour);
    if (!day->head) {
        day->head = newNode;
    } else {
        Node* temp = day->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    std::cout << "Train added to " << day->dayName << " schedule.\n";
}

// Function of adding train schedules
void addTrainSchedule(int trainID, const std::string& destination, const std::string& trainName, int hour) {
    if (!weekQueueHead) {
        std::cout << "No day schedule available. Initialize the week queue first.\n";
        return;
    }
    enqueueTrain(weekQueueHead, trainID, destination, trainName, hour);
}

// Dequeue function to delete the first train from the schedule list on a given day
void dequeueTrain(DayNode* day) {
    if (day->head == nullptr) {  // If theres no schedule 
        std::cout << "No train schedule to delete.\n";
        return;
    }

    Node* temp = day->head;
    day->head = day->head->next;

    delete temp;
    std::cout << "First Train schedule deleted.\n";
}


// Function to delete the first train schedule of the current day
void deleteTrainSchedule() {
    if (weekQueueHead == nullptr) {
        std::cout << "No day schedule available.\n";
        return;
    }
    dequeueTrain(weekQueueHead);
}


// Display today's schedule
void displaySchedule(const DayNode* day) {
    Node* temp = day->head;
    while (temp != nullptr) {
        // Convert the hour to a formatted string
        int hour = temp->hour;
        std::string ampm = "AM";
        int displayHour = hour / 100; // Get the hour part
        int minutes = hour % 100;    // Get the minutes part
        
        if (displayHour >= 12) {
            ampm = "PM";
            if (displayHour > 12) {
                displayHour -= 12;  // Convert to 12-hour format
            }
        }

        if (displayHour == 0) {
            displayHour = 12;  // Midnight case (00:00 is 12:00 AM)
        }

        // Print the train details with formatted hour
        std::cout << "Train ID: " << temp->trainID
                  << ", Destination: " << temp->destination
                  << ", Train Name: " << temp->trainName
                  << ", Hour: " << displayHour << ":"
                  << (minutes < 10 ? "0" : "") << minutes  // Ensure two digits for minutes
                  << " " << ampm << std::endl;

        temp = temp->next;
    }
}


// The function displays today's schedule
void displayTodaySchedule() {
    if (weekQueueHead == nullptr) {
        std::cout << "No day schedule available.\n";
        return;
    }
    std::cout << "Today's Schedule (" << weekQueueHead->dayName << "):\n";
    displaySchedule(weekQueueHead);
}

// Function to advance one day to the next day
void advanceToNextDay() {
    if (weekQueueHead == nullptr) return;
    DayNode* temp = weekQueueHead;
    weekQueueHead = weekQueueHead->next;
    delete temp;
    if (weekQueueHead == nullptr) {
        initializeWeekQueue(); 
    }
}

void updateTrainSchedule(int trainID, int newHour) {
    if (weekQueueHead == nullptr) {
        std::cout << "No day schedule available.\n";
        return;
    }

    // Check if any train already has the newHour
    Node* current = weekQueueHead->head;
    while (current != nullptr) {
        if (current->hour == newHour) {
            std::cout << "A train is already scheduled to depart at " << newHour << ". Cannot update to the same hour.\n";
            return;
        }
        current = current->next;
    }

    // Reset current pointer to head to search for trainID
    current = weekQueueHead->head;
    bool found = false;

    // Search for trainID and update its hour
    while (current != nullptr) {
        if (current->trainID == trainID) {
            current->hour = newHour;
            std::cout << "Train schedule updated for Train ID " << trainID << " to new hour " << newHour << ".\n";
            found = true;
            break; 
        }
        current = current->next;
    }

    if (!found) {
        std::cout << "Train ID " << trainID << " not found in today's schedule.\n";
    }
}


// QuickSort partition function for linked list
Node* partition(Node* low, Node* high, Node** newLow, Node** newHigh) {
    Node* pivot = high;
    Node* prev = nullptr, *cur = low, *tail = pivot;

    while (cur != pivot) {
        if (cur->hour < pivot->hour) {
            if ((*newLow) == nullptr) (*newLow) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }
    if ((*newLow) == nullptr) (*newLow) = pivot;
    (*newHigh) = tail;
    return pivot;
}

// Get the last node in a linked list
Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

// Recursive QuickSort helper for linked list
Node* quickSortHelper(Node* low, Node* high) {
    if (!low || low == high) return low;

    Node* newLow = nullptr, *newHigh = nullptr;
    Node* pivot = partition(low, high, &newLow, &newHigh);

    if (newLow != pivot) {
        Node* temp = newLow;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newLow = quickSortHelper(newLow, temp);

        temp = getTail(newLow);
        temp->next = pivot;
    }

    pivot->next = quickSortHelper(pivot->next, newHigh);
    return newLow;
}

// QuickSort main function for today's schedule
void quickSort() {
    if (weekQueueHead && weekQueueHead->head) {
        weekQueueHead->head = quickSortHelper(weekQueueHead->head, getTail(weekQueueHead->head));
        std::cout << "Today's schedule sorted by Train ID (Quick Sort):\n";
        displayTodaySchedule();  // Display the sorted schedule
    }
}

// Merge function to merge two sorted linked lists for merge sort
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->trainName < right->trainName) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

// Get the middle node of a linked list for merge sort
Node* getMiddle(Node* head) {
    if (head == nullptr) return head;
    Node* slow = head;
    Node* fast = head->next;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Recursive MergeSort helper function for linked list
Node* mergeSortHelper(Node* head) {
    if (!head || !head->next) return head;

    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->next;
    middle->next = nullptr;

    Node* left = mergeSortHelper(head);
    Node* right = mergeSortHelper(nextOfMiddle);

    return merge(left, right);
}

// MergeSort main function for today's schedule
void mergeSort() {
    if (weekQueueHead && weekQueueHead->head) {
        weekQueueHead->head = mergeSortHelper(weekQueueHead->head);
        std::cout << "Today's schedule sorted by Train Name:\n";
        displayTodaySchedule();  // Display the sorted schedule
    }
}

// Counts the number of nodes in a linked list
int countNodes(Node* head) {
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;
    }
    return count;
}

void fibonacciSearchByTrainID(int trainID) {
    if (!weekQueueHead || !weekQueueHead->head) {
        std::cout << "No train schedule available.\n";
        return;
    }

    // Calculate Fibonacci numbers
    int fibMMm2 = 0;  // (m-2)'th Fibonacci number
    int fibMMm1 = 1;  // (m-1)'th Fibonacci number
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci number

    int nodeCount = countNodes(weekQueueHead->head); // Count the nodes (schedule entries)

    // Find the smallest Fibonacci number greater than or equal to the number of nodes
    while (fibM < nodeCount) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;  // Marks the eliminated range from the front
    Node* current = weekQueueHead->head;

    // Perform the Fibonacci search
    while (fibM > 1) {
        // Find the valid index to compare, offset + fibMMm2
        int i = std::min(offset + fibMMm2, nodeCount - 1);

        // Move to the node at index `i`
        Node* temp = current;
        for (int j = 0; j < i && temp; j++) {
            temp = temp->next;
        }

        if (!temp) break;

        if (temp->trainID < trainID) {
            // Shift range: fibMMm1 becomes fibM, fibMMm2 becomes fibMMm1
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;  // Update offset
        } else if (temp->trainID > trainID) {
            // Shift range: fibMMm2 becomes fibM, fibMMm1 becomes fibMMm2
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            // Train found
            std::cout << "Train ID " << trainID << " found. Details:\n";
            std::cout << "Destination: " << temp->destination << ", Train Name: " << temp->trainName
                      << ", Departure Hour: " << temp->hour / 100 << ":"
                      << (temp->hour % 100 < 10 ? "0" : "") << temp->hour % 100 << "\n";
            return;
        }
    }

    // Check the last possible element
    if (fibMMm1 && current && current->trainID == trainID) {
        std::cout << "Train ID " << trainID << " found. Details:\n";
        std::cout << "Destination: " << current->destination << ", Train Name: " << current->trainName
                  << ", Departure Hour: " << current->hour / 100 << ":"
                  << (current->hour % 100 < 10 ? "0" : "") << current->hour % 100 << "\n";
        return;
    }

    std::cout << "Train ID " << trainID << " not found.\n";
}


int* collecthours(int& numTrains) {
    if (!weekQueueHead || !weekQueueHead->head) {
        numTrains = 0;
        return nullptr;
    }

    numTrains = 0;
    Node* current = weekQueueHead->head;
    while (current != nullptr) {
        numTrains++;
        current = current->next;
    }

    int* hours = new int[numTrains];
    current = weekQueueHead->head;
    for (int i = 0; i < numTrains; i++) {
        hours[i] = current->hour;
        current = current->next;
    }
    return hours;
}

void jumpSearchByDeparture(int hour) {
    int numTrains;
    int* hours = collecthours(numTrains);  // Collect all train departure hours

    if (numTrains == 0) {
        std::cout << "No train schedule available.\n";
        return;
    }

    int step = std::sqrt(numTrains);  // Jump step
    int prev = 0;

    // Find the block where the hour might be present
    while (hours[std::min(step, numTrains) - 1] < hour) {
        prev = step;
        step += std::sqrt(numTrains);
        if (prev >= numTrains) {
            std::cout << "Departure hour " << hour << " not found.\n";
            delete[] hours;
            return;
        }
    }

    // Perform a linear search within the identified block
    while (prev < std::min(step, numTrains) && hours[prev] < hour) {
        prev++;
    }

    // Check if the hour is present
    if (prev < numTrains && hours[prev] == hour) {
        std::cout << "Departure hour " << hour << " found. Here is the schedule:\n";

        // Traverse the weekly queue and display trains matching the hour
        DayNode* currentDay = weekQueueHead;
        bool found = false;

        while (currentDay != nullptr) {
            Node* temp = currentDay->head;
            while (temp != nullptr) {
                if (temp->hour == hour) {
                    if (!found) {
                        std::cout << "Train(s) departing at " << hour << ":\n";
                    }
                    std::cout << "Day: " << currentDay->dayName << std::endl;
                    std::cout << "  Train ID: " << temp->trainID
                              << ", Destination: " << temp->destination
                              << ", Train Name: " << temp->trainName
                              << ", Hour: " << hour / 100 << ":"
                              << (hour % 100 < 10 ? "0" : "") << hour % 100
                              << std::endl;
                    found = true;
                }
                temp = temp->next;
            }
            currentDay = currentDay->next;
        }

        if (!found) {
            std::cout << "No trains found departing at " << hour << ".\n";
        }
    } else {
        std::cout << "Departure hour " << hour << " not found.\n";
    }

    delete[] hours;  // Free dynamically allocated memory
}


void badCharHeuristic(const std::string& trainName, int badChar[256]) {
    // Initialize all occurrences as -1
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    // Populate the actual last occurrence of each character in the pattern
    for (int i = 0; i < trainName.size(); i++) {
        badChar[(int)trainName[i]] = i;
    }
}


void boyerMooreSearchByName(const std::string& targetName) {
    if (!weekQueueHead) {
        std::cout << "No train schedule available.\n";
        return;
    }

    DayNode* currentDay = weekQueueHead;
    bool found = false;

    while (currentDay != nullptr) {
        Node* temp = currentDay->head;  // Start from the first train of the day
        while (temp != nullptr) {
            int m = targetName.size();
            int n = temp->trainName.size();

            int badChar[256];
            badCharHeuristic(targetName, badChar);

            int shift = 0;  // Shift of the pattern with respect to text
            while (shift <= (n - m)) {
                int j = m - 1;

                // Reduce index j of pattern while characters of pattern and text match
                while (j >= 0 && targetName[j] == temp->trainName[shift + j]) {
                    j--;
                }

                // If the pattern matches the substring of text
                if (j < 0) {
                    std::cout << "Train Name \"" << targetName << "\" found on " << currentDay->dayName << ".\n";
                    std::cout << "Details:\n";
                    std::cout << "  Train ID: " << temp->trainID << "\n";
                    std::cout << "  Destination: " << temp->destination << "\n";
                    std::cout << "  Departure Hour: " << temp->hour << "\n";
                    found = true;
                    break;
                } else {
                    // Shift the pattern
                    shift += std::max(1, j - badChar[(int)temp->trainName[shift + j]]);
                }
            }

            if (found) break;
            temp = temp->next;  // Move to the next train
        }

        if (found) break;
        currentDay = currentDay->next;  // Move to the next day's schedule
    }

    if (!found) {
        std::cout << "Train Name \"" << targetName << "\" not found in the weekly schedule.\n";
    }
}