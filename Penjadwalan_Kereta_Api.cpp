#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
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

// Utility function to collect train nodes for sorting
std::vector<Node*> collectTrains() {
    std::vector<Node*> trains;
    DayNode* currentDay = weekQueueHead;
    while (currentDay != nullptr) {
        Node* train = currentDay->head;
        while (train != nullptr) {
            trains.push_back(train);
            train = train->next;
        }
        currentDay = currentDay->next;
    }
    return trains;
}

void quickSort() {
    std::cout << "Quick sort algorithm executed.\n";
    // Quick sort logic here
}

void mergeSort() {
    std::cout << "Merge sort algorithm executed.\n";
    // Merge sort logic here
}

void fibonacciSearch(int trainID) {
    std::cout << "Fibonacci search executed for Train ID: " << trainID << std::endl;
    // Fibonacci search logic here
}

void jumpSearch(int trainID) {
    std::vector<Node*> trains = collectTrains();  // Get today's sorted train schedule
    int n = trains.size();                        // Number of trains in today's schedule
    int step = sqrt(n);                           // Optimal jump step size
    int prev = 0;

    // Step 1: Jump forward by step size until we exceed or find the target
    while (trains[std::min(step, n) - 1]->trainID < trainID) {
        prev = step;                              // Move to the next block
        step += sqrt(n);
        if (prev >= n) {                          // If we've jumped past the end of the list
            std::cout << "Train ID " << trainID << " not found.\n";
            return;
        }
    }

    // Step 2: Perform a linear search in the identified block
    while (trains[prev]->trainID < trainID) {
        prev++;
        if (prev == std::min(step, n)) {          // Reached the end of the block
            std::cout << "Train ID " << trainID << " not found.\n";
            return;
        }
    }
    
    // Check if the element at `prev` is the target
    if (trains[prev]->trainID == trainID) {
        std::cout << "Train ID " << trainID << " found.\n";
    } else {
        std::cout << "Train ID " << trainID << " not found.\n";
    }
}


// Utility function to build the bad character heuristic for integer values
void badCharHeuristic(const std::vector<int>& trainIDs, int badChar[256]) {
    // Initialize all occurrences as -1
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }
    // Populate last occurrence of each character (trainID mod 256) in the trainIDs vector
    for (int i = 0; i < trainIDs.size(); i++) {
        badChar[trainIDs[i] % 256] = i;
    }
}

// Boyer-Moore search for finding trainID in today's schedule
void boyerMooreSearch(int trainID) {
    std::vector<Node*> trains = collectTrains();  // Get today's schedule as a sorted list of train nodes
    int n = trains.size();
    if (n == 0) {
        std::cout << "No train schedule available.\n";
        return;
    }

    // Extract train IDs into a vector of integers for easier comparison
    std::vector<int> trainIDs;
    for (const auto& train : trains) {
        trainIDs.push_back(train->trainID);
    }

    // Build bad character table for trainIDs
    int badChar[256];
    badCharHeuristic(trainIDs, badChar);

    // Boyer-Moore search logic
    int shift = 0;  // `shift` is the offset of the current position
    while (shift <= n - 1) {
        int j = n - 1;  // Start comparing from the end of the pattern

        // Check if the trainID matches at the current position
        while (j >= 0 && trainIDs[shift + j] == trainID) {
            j--;
        }

        // If the pattern is found at the current shift
        if (j < 0) {
            std::cout << "Train ID " << trainID << " found in today's schedule.\n";
            return;
        }

        // Shift the pattern based on the bad character heuristic
        int badCharIndex = trainID % 256;  // Modulus to fit within the table range
        shift += std::max(1, j - badChar[badCharIndex]);
    }

    // If not found
    std::cout << "Train ID " << trainID << " not found in today's schedule.\n";
}
