#include <iostream>
#include <chrono>
#include <thread>
#include <string>

// Function Prototypes
int jeda();
bool isInteger(const std::string& str);
bool isFloat(const std::string& str);
int menu();
void initializeWeekQueue(); //Dika           
void addTrainSchedule(int trainID, const std::string& destination); //Dika
void deleteTrainSchedule(); //Dika
void displayTodaySchedule(); //Dika       
void advanceToNextDay(); //Dika                
void enqueueDay(const std::string& day); //Kiki
void enqueueTrain(struct DayNode* day, int trainID, const std::string& destination, int hour); //Kiki
void deleteTrain(struct DayNode* day); //Kiki
void displaySchedule(const struct DayNode* day); //Kiki          
void updateTrainSchedule(int trainID, int newHour); //Kiki
void quickSort(); //Rava
void mergeSort(); //Rava
void fibonacciSearch(int trainID); //Rava
void jumpSearch(int trainID); //Rava
void boyerMooreSearch(int trainID); //Rava

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
    std::cout << "[1] Initialize Week Queue          " << std::endl;
    std::cout << "[2] Add Train Schedule             " << std::endl;
    std::cout << "[3] Update Train Schedule          " << std::endl;
    std::cout << "[4] Delete Train Schedule          " << std::endl;
    std::cout << "[5] Display Today's Schedule       " << std::endl;
    std::cout << "[6] Advance to Next Day            " << std::endl;
    std::cout << "[7] Quick Sort                     " << std::endl;
    std::cout << "[8] Merge Sort                     " << std::endl;
    std::cout << "[9] Fibonacci Search               " << std::endl;
    std::cout << "[10] Jump Search                   " << std::endl;
    std::cout << "[11] Boyer-Moore Search            " << std::endl;
    std::cout << "[0] Exit                           " << std::endl;
    std::cout << "Enter choice:                      ";
    std::cin >> pilihan;
    return pilihan;
}

// Fungsi untuk menambahkan hari ke antrian minggu (linked list)
void enqueueDay(const std::string& day) {
    DayNode* newDay = new DayNode(day);
    if (weekQueueHead == nullptr) {
        weekQueueHead = newDay;
        std::cout << "New Week Has Been Initialized ";
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

// Advance to next day in the week queue
void advanceToNextDay() {
    if (weekQueueHead == nullptr) return;
    DayNode* temp = weekQueueHead;
    weekQueueHead = weekQueueHead->next;
    delete temp;
    if (weekQueueHead == nullptr) {
        initializeWeekQueue();  // Reinitialize the week if we have gone through all days
    }
}

void updateTrainSchedule(int trainID, int newHour) {
    std::cout << "Train Schedule updated.\n";
    // Update train schedule logic here
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
    std::cout << "Jump search executed for Train ID: " << trainID << std::endl;
    // Jump search logic here
}

void boyerMooreSearch(int trainID) {
    std::cout << "Boyer-Moore search executed for Train ID: " << trainID << std::endl;
    // Boyer-Moore search logic here
}
