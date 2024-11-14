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
    std::cout << "Enter choice:";
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

// Mengembalikan pointer ke node terakhir dari linked list
Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

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

void quickSort() {
    if (weekQueueHead && weekQueueHead->head) {
        weekQueueHead->head = quickSortHelper(weekQueueHead->head, getTail(weekQueueHead->head));
        std::cout << "Today's schedule sorted by Train ID (Quick Sort).\n";
    }
}

// Fungsi merge untuk menggabungkan dua linked list terurut di merge sort
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

// Mengembalikan pointer ke node tengah dari linked list untuk merge sort
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

// Fungsi utama merge sort
Node* mergeSortHelper(Node* head) {
    if (!head || !head->next) return head;

    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->next;
    middle->next = nullptr;

    Node* left = mergeSortHelper(head);
    Node* right = mergeSortHelper(nextOfMiddle);

    return merge(left, right);
}

void mergeSort() {
    if (weekQueueHead && weekQueueHead->head) {
        weekQueueHead->head = mergeSortHelper(weekQueueHead->head);
        std::cout << "Today's schedule sorted by Train ID (Merge Sort).\n";
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

void jumpSearch(int trainID) {
    std::cout << "Jump search executed for Train ID: " << trainID << std::endl;
    // Jump search logic here
}

void boyerMooreSearch(int trainID) {
    std::cout << "Boyer-Moore search executed for Train ID: " << trainID << std::endl;
    // Boyer-Moore search logic here
}
