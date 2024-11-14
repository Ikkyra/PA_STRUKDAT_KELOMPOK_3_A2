#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <bits/stdc++.h> //sqrt for jumpsearch to work 


// Function Prototypes
int jeda();
bool isInteger(const std::string& str);
bool isFloat(const std::string& str);
int menu();
void initializeWeekQueue();          
void addTrainSchedule(int trainID, const std::string& destination); 
void deleteTrainSchedule(); 
void displayTodaySchedule(); 
void advanceToNextDay(); 
void enqueueDay(const std::string& day); 
void enqueueTrain(struct DayNode* day, int trainID, const std::string& destination, int hour); 
void deleteTrain(struct DayNode* day); 
void displaySchedule(const struct DayNode* day);           
void updateTrainSchedule(int trainID, int newHour); 
void quickSort(); 
void mergeSort(); 
void fibonacciSearch(int trainID); 
void jumpSearch(int trainID); 
void boyerMooreSearch(int trainID); 

// Define Node structure for single linked list
struct Node {
    int trainID;
    std::string destination;
    int hour;
    Node* next;

    Node(int id, const std::string& dest, int h) 
        : trainID(id), destination(dest), hour(h), next(nullptr) {}
};

// Node untuk hari-hari dalam satu minggu (pengganti `queue`)
struct DayNode {
    std::string dayName;
    Node* head;
    DayNode* next;
    int availableHours[24];

    DayNode(const std::string& day) : dayName(day), head(nullptr), next(nullptr) {
        for (int i = 0; i < 24; ++i) availableHours[i] = i;
    }
};

// Global head pointer untuk queue minggu
DayNode* weekQueueHead = nullptr;

// Main Function
int main() {
    int choice;
    int trainID;
    std::string destination;
    int newHour;

    while ((choice = menu()) != 0) {
        switch(choice) {
            case 1:
                initializeWeekQueue();
                break;
            case 2:
                std::cout << "Enter Train ID: ";
                std::cin >> trainID;
                std::cout << "Enter Destination: ";
                std::cin >> destination;
                addTrainSchedule(trainID, destination);
                break;
            case 3:
                std::cout << "Enter Train ID to Update: ";
                std::cin >> trainID;
                std::cout << "Enter New Hour: ";
                std::cin >> newHour;
                updateTrainSchedule(trainID, newHour);
                break;
            case 4:
                std::cout << "Enter Train ID to Delete: ";
                std::cin >> trainID;
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
                std::cout << "Enter Train ID for Fibonacci Search: ";
                std::cin >> trainID;
                fibonacciSearch(trainID);
                break;
            case 10:
                std::cout << "Enter Train ID for Jump Search: ";
                std::cin >> trainID;
                jumpSearch(trainID);
                break;
            case 11:
                std::cout << "Enter Train ID for Boyer-Moore Search: ";
                std::cin >> trainID;
                boyerMooreSearch(trainID);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
        jeda();
    }
    return 0;
}

// Function Implementations

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
    std::cout << "[7] Quick Sort                     " << std::endl; // rava
    std::cout << "[8] Merge Sort                     " << std::endl; // rava
    std::cout << "[9] Fibonacci Search               " << std::endl; // rava
    std::cout << "[10] Jump Search                   " << std::endl; // kiki
    std::cout << "[11] Boyer-Moore Search            " << std::endl; // kiki
    std::cout << "[0] Exit                           " << std::endl;
    std::cout << "Enter choice: ";
    std::cin >> pilihan;
    return pilihan;
}

// Fungsi untuk menambahkan hari ke antrian minggu (linked list)
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

// Menginisialisasi antrian minggu dengan nama hari
void initializeWeekQueue() {
    const char* days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; ++i) {
        enqueueDay(days[i]);
    }
}

// Enqueue (add to the end of the list) a train schedule
void enqueueTrain(DayNode* day, int trainID, const std::string& destination, int hour) {
    Node* newNode = new Node(trainID, destination, hour);
    if (day->head == nullptr) {
        day->head = newNode;
    } else {
        Node* temp = day->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi menambahkan jadwal kereta
void addTrainSchedule(int trainID, const std::string& destination) {
    if (weekQueueHead == nullptr) {
        std::cout << "No day schedule available. Initialize the week queue first.\n";
        return;
    }
    int hour;
    std::cout << "Enter Hour: ";
    std::cin >> hour;
    enqueueTrain(weekQueueHead, trainID, destination, hour);
}

// Fungsi dequeue untuk menghapus kereta pertama dari daftar jadwal pada hari tertentu
void dequeueTrain(DayNode* day) {
    if (day->head == nullptr) {  // Jika tidak ada jadwal
        std::cout << "No train schedule to delete.\n";
        return;
    }

    // Simpan pointer ke elemen pertama dan pindahkan head ke elemen berikutnya
    Node* temp = day->head;
    day->head = day->head->next;

    // Hapus elemen pertama
    delete temp;
    std::cout << "First train schedule deleted.\n";
}


// Fungsi untuk menghapus jadwal kereta pertama pada hari saat ini
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
        std::cout << "Train ID: " << temp->trainID 
                  << ", Destination: " << temp->destination 
                  << ", Hour: " << temp->hour << std::endl;
        temp = temp->next;
    }
}

// Fungsi menampilkan jadwal hari ini
void displayTodaySchedule() {
    if (weekQueueHead == nullptr) {
        std::cout << "No day schedule available.\n";
        return;
    }
    std::cout << "Today's Schedule (" << weekQueueHead->dayName << "):\n";
    displaySchedule(weekQueueHead);
}

// Fungsi untuk memajukan hari ke hari berikutnya
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
    
    Node* current = weekQueueHead->head;
    bool found = false;

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
        if (cur->trainID < pivot->trainID) {
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

    if (left->trainID < right->trainID) {
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
        std::cout << "Today's schedule sorted by Train ID (Merge Sort):\n";
        displayTodaySchedule();  // Display the sorted schedule
    }
}

// Menghitung jumlah node dalam linked list
int countNodes(Node* head) {
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;
    }
    return count;
}

void fibonacciSearch(int trainID) {
    Node* head = weekQueueHead->head;
    int fibMMm2 = 0, fibMMm1 = 1, fibM = fibMMm2 + fibMMm1;
    int offset = -1;

    while (head && fibM < countNodes(head)) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    Node* current = head;
    while (current) {
        if (current->trainID == trainID) {
            std::cout << "Train ID " << trainID << " found.\n";
            return;
        }
        current = current->next;
    }
    std::cout << "Train ID " << trainID << " not found.\n";

}

int* collectTrainIDs(int& numTrains) {
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

    int* trainIDs = new int[numTrains];
    current = weekQueueHead->head;
    for (int i = 0; i < numTrains; i++) {
        trainIDs[i] = current->trainID;
        current = current->next;
    }
    return trainIDs;
}

// Jump search implementation without using std::vector
void jumpSearch(int trainID) {
    int numTrains;
    int* trainIDs = collectTrainIDs(numTrains); 

    if (numTrains == 0) {
        std::cout << "No train schedule available.\n";
        return;
    }

    int step = std::sqrt(numTrains);
    int prev = 0;

    while (trainIDs[std::min(step, numTrains) - 1] < trainID) {
        prev = step;
        step += std::sqrt(numTrains);
        if (prev >= numTrains) {  
            std::cout << "Train ID " << trainID << " not found.\n";
            delete[] trainIDs;
            return;
        }
    }

    while (trainIDs[prev] < trainID) {
        prev++;
        if (prev == std::min(step, numTrains)) { 
            std::cout << "Train ID " << trainID << " not found.\n";
            delete[] trainIDs; 
            return;
        }
    }

    // Check if we found the train ID
    if (trainIDs[prev] == trainID) {
        std::cout << "Train ID " << trainID << " found.\n";
    } else {
        std::cout << "Train ID " << trainID << " not found.\n";
    }

    delete[] trainIDs;  // Free dynamically allocated memory
}

void badCharHeuristic(int* trainIDs, int size, int badChar[256]) {
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;  
    }
    for (int i = 0; i < size; i++) {
        badChar[trainIDs[i] % 256] = i;  
    }
}

void boyerMooreSearch(int trainID) {
    int numTrains;
    int* trainIDs = collectTrainIDs(numTrains);

    if (numTrains == 0) {
        std::cout << "No train schedule available.\n";
        return;
    }

    int badChar[256];
    badCharHeuristic(trainIDs, numTrains, badChar);

    int shift = 0;
    while (shift <= (numTrains - 1)) {
        int j = numTrains - 1; 

        while (j >= 0 && trainIDs[shift + j] == trainID) {
            j--;
        }

        if (j < 0) {
            std::cout << "Train ID " << trainID << " found in today's schedule.\n";
            delete[] trainIDs; 
            return;
        }

        int badCharIndex = trainID % 256; 
        shift += std::max(1, j - badChar[badCharIndex]);
    }

    std::cout << "Train ID " << trainID << " not found in today's schedule.\n";
    delete[] trainIDs;  
}