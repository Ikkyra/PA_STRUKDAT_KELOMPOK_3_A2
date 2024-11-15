#include <iostream>
#include <chrono> //
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
// Stack
void addTrainSchedule(int trainID, const std::string& destination, const std::string& trainName, int hour);
void enqueueDay(const std::string& day);
void pushTrain(struct DayNode* day, int trainID, const std::string& destination, const std::string& trainName, int hour);
void deleteTrainSchedule();
void displayTodaySchedule();
void updateTrainSchedule(int trainID, int newHour);
// Sort
void quickSort(int check);
void mergeSort();
// Search
void fibonacciSearchByTrainID(int trainID);
void jumpSearchByDeparture(int hour);
void boyerMooreSearchByName(const std::string& trainName);

// Mendefinisikan struktur node untuk single linked list
struct Node {
    int trainID;
    std::string destination;
    std::string trainName;
    int hour;
    Node* next;

    Node(int id, const std::string& dest, const std::string& name, int h)
        : trainID(id), destination(dest), trainName(name), hour(h), next(nullptr) {}
};

// Mendefinisikan node untuk tiap hari didalam linkedlist yang merepresentasikan hari diminggu tersebut
struct DayNode {
    std::string dayName;
    Node* head;
    DayNode* next;

    DayNode(const std::string& day) : dayName(day), head(nullptr), next(nullptr) {}
};

// Global head pointer untuk minggu, nullptr karena belum di inisialisasi
DayNode* weekQueueHead = nullptr;

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
                quickSort(0);
                break;

            case 8:
                mergeSort();
                break;

            case 9:
                quickSort(1);
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

// Digunakan untuk "mem-pause" program selama 2 detik
int jeda() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}

// Digunakan untuk mengecek apakah input merupakan integer
bool isInteger(const std::string& str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

// Digunakan untuk mengecek apakah input merupakan float
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
    std::cout << "[7] Sort by Train Departure        " << std::endl; 
    std::cout << "[8] Sort by Train Name             " << std::endl; 
    std::cout << "[9] Search by Train Id             " << std::endl; 
    std::cout << "[10] Search by Train Departure     " << std::endl; 
    std::cout << "[11] Search by Train Name          " << std::endl; 
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

// Menambah hari kedalam queue mingguan (Linked List)
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

// Inisialisasi minggu dengan nama hari
void initializeWeekQueue() {
    const char* days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; ++i) {
        enqueueDay(days[i]);
    }
}

// Menambahkan jadwal kereta ke hari tertentu
void pushTrain(DayNode* day, int trainID, const std::string& destination, const std::string& trainName, int hour) {
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

    // Stack
    newNode->next = day->head;
    day->head = newNode;

    std::cout << "Train added to " << day->dayName << " schedule.\n";
}

// Menambahkan jadwal kereta
void addTrainSchedule(int trainID, const std::string& destination, const std::string& trainName, int hour) {
    if (!weekQueueHead) {
        std::cout << "No day schedule available. Initialize the week queue first.\n";
        return;
    }
    pushTrain(weekQueueHead, trainID, destination, trainName, hour);
}

// Menghapus Kereta pertama dari list jadwal pada hari tertentu
void dequeueTrain(DayNode* day) {
    if (day->head == nullptr) {  // Jika Tidak jadwal
        std::cout << "No train schedule to delete.\n";
        return;
    }

    Node* temp = day->head;
    day->head = day->head->next;

    delete temp;
    std::cout << "First Train schedule deleted.\n";
}


// Digunakan untuk Menghapus Train Schedule
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
        // Mengubah Hour ke format jam dan menit
        int hour = temp->hour;
        std::string ampm = "AM";
        int displayHour = hour / 100; // Untuk waktu jam
        int minutes = hour % 100;    // Untuk Waktu Menit
        
        if (displayHour >= 12) {
            ampm = "PM";
            if (displayHour > 12) {
                displayHour -= 12;  // mengubah ke foramt 12 jam
            }
        }

        std::cout << "Train ID: " << temp->trainID
                  << ", Destination: " << temp->destination
                  << ", Train Name: " << temp->trainName
                  << ", Hour: " << displayHour << ":"
                  << (minutes < 10 ? "0" : "") << minutes  // Memastikan dua digit untuk menit
                  << " " << ampm << std::endl;

        temp = temp->next;
    }
}


// Fungsi untuk menampilkan jadwal hari ini
void displayTodaySchedule() {
    if (weekQueueHead == nullptr) {
        std::cout << "No day schedule available.\n";
        return;
    }
    std::cout << "Today's Schedule (" << weekQueueHead->dayName << "):\n";
    displaySchedule(weekQueueHead);
}

// Memajukan Head list ke hari selanjutnya dan menghapus head list sebelumnya
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

    // mengecek apakah kereta lain sudah memiliki jam baru yang diubah
    Node* current = weekQueueHead->head;
    while (current != nullptr) {
        if (current->hour == newHour) {
            std::cout << "A train is already scheduled to depart at " << newHour << ". Cannot update to the same hour.\n";
            return;
        }
        current = current->next;
    }

    // Reset pointer skrg ke head untuk mencari trainID
    current = weekQueueHead->head;
    bool found = false;

    // Mencari Train ID dan mengupdate jamnya
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


// Partisi linked list untuk QuickSort yang membagi linked list menjadi dua bagian
Node* partition(int check, Node* low, Node* high, Node** newLow, Node** newHigh) {
    Node* pivot = high;
    Node* prev = nullptr, *cur = low, *tail = pivot;

    while (cur != pivot) {
        if(check == 1){
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
        }else{
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
    }
    if ((*newLow) == nullptr) (*newLow) = pivot;
    (*newHigh) = tail;
    return pivot;
}

// Mengambil node terakhir di linked list
Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

// Fungsi quicksort rekursif untuk linked list
Node* quickSortHelper(int check, Node* low, Node* high) {
    if (!low || low == high) return low;

    Node* newLow = nullptr, *newHigh = nullptr;
    Node* pivot = partition(check, low, high, &newLow, &newHigh);

    if (newLow != pivot) {
        Node* temp = newLow;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newLow = quickSortHelper(check, newLow, temp);

        temp = getTail(newLow);
        temp->next = pivot;
    }

    pivot->next = quickSortHelper(check, pivot->next, newHigh);
    return newLow;
}

// Fungsi utama quicksort untuk jadwal hari ini
void quickSort(int check) {
    if (weekQueueHead && weekQueueHead->head) {
        weekQueueHead->head = quickSortHelper(check ,weekQueueHead->head, getTail(weekQueueHead->head));
        if (check == 0) {
        std::cout << "Today's schedule sorted by Train ID (Quick Sort):\n";
        displayTodaySchedule();  // Menampilkan jadwal yang sudah diurutkan
        }
    }
}

// Fungsi merge untuk menggabungkan dua linked list yang sudah diurutkan untuk merge sort
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

// Mengambilkan node tengah dari linked list untuk merge sort
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

// Fungsi bantu MergeSort rekursif untuk linked list
Node* mergeSortHelper(Node* head) {
    if (!head || !head->next) return head;

    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->next;
    middle->next = nullptr;

    Node* left = mergeSortHelper(head);
    Node* right = mergeSortHelper(nextOfMiddle);

    return merge(left, right);
}

// Fungsi utama MergeSort untuk jadwal hari ini
void mergeSort() {

    if (weekQueueHead && weekQueueHead->head) {
        weekQueueHead->head = mergeSortHelper(weekQueueHead->head);
        std::cout << "Today's schedule sorted by Train Name:\n";
        displayTodaySchedule();
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

void fibonacciSearchByTrainID(int trainID) {
    if (!weekQueueHead || !weekQueueHead->head) {
        std::cout << "No train schedule available.\n";
        return;
    }

    // Cek elemen pertama sebelum memulai perhitungan Fibonacci
    if (weekQueueHead->head->trainID == trainID) {
        std::cout << "Train ID " << trainID << " found. Details:\n";
        std::cout << "Destination: " << weekQueueHead->head->destination << "\n";
        std::cout << "Train Name: " << weekQueueHead->head->trainName << "\n";
        std::cout << "Departure Hour: " << weekQueueHead->head->hour / 100 << ":"
                  << (weekQueueHead->head->hour % 100 < 10 ? "0" : "") << weekQueueHead->head->hour % 100 << "\n";
        return;  // Selesai, karena sudah ditemukan di elemen pertama
    }

    int nodeCount = countNodes(weekQueueHead->head); // Jumlah node dalam jadwal
    const Node* current = weekQueueHead->head;

    // Hitung bilangan Fibonacci yang lebih besar atau sama dengan jumlah node
    int fibM2 = 0; 
    int fibM1 = 1;
    int fibM = fibM2 + fibM1; 

    while (fibM < nodeCount) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }

    int offset = -1;  // Menandai elemen terakhir yang diperiksa

    // Lakukan pencarian Fibonacci
    while (fibM > 1) {
        // Cari indeks yang valid untuk dibandingkan
        int i = std::min(offset + fibM2, nodeCount - 1);

        // Pindahkan ke node pada indeks i
        const Node* temp = current;
        for (int j = 0; j <= i && temp; j++) {
            temp = temp->next;
        }

        if (!temp) break;

        if (temp->trainID < trainID) {
            // Geser rentang: fibM1 menjadi fibM, fibM2 menjadi fibM1
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;  // Perbarui offset
        } else if (temp->trainID > trainID) {
            // Geser rentang: fibM2 menjadi fibM, fibM1 menjadi fibM2
            fibM = fibM2;
            fibM1 -= fibM2;
            fibM2 = fibM - fibM1;
        } else {
            // Kereta ditemukan
            std::cout << "Train ID " << trainID << " found. Details:\n";
            std::cout << "Destination: " << temp->destination << "\n";
            std::cout << "Departure Hour: " << temp->hour / 100 << ":"
                      << (temp->hour % 100 < 10 ? "0" : "") << temp->hour % 100 << "\n";
            return;
        }
    }

    // Periksa elemen terakhir
    if (fibM1 && current && current->trainID == trainID) {
        std::cout << "Train ID " << trainID << " found. Details:\n";
        std::cout << "Destination: " << current->destination << "\n";
        std::cout << "Departure Hour: " << current->hour / 100 << ":"
                  << (current->hour % 100 < 10 ? "0" : "") << current->hour % 100 << "\n";
        return;
    }

    std::cout << "Train ID " << trainID << " not found.\n";
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
    int* hours = collecthours(numTrains);  // mendapatkan semua jam keberangkatan

    if (numTrains == 0) {
        std::cout << "No train schedule available.\n";
        return;
    }

    int step = std::sqrt(numTrains); 
    int prev = 0;

    // Mencari blok dimana jam mungkin ada
    while (hours[std::min(step, numTrains) - 1] < hour) {
        prev = step;
        step += std::sqrt(numTrains);
        if (prev >= numTrains) {
            std::cout << "Departure hour " << hour << " not found.\n";
            delete[] hours;
            return;
        }
    }

    // Menjalankan pencarian linier dalam blok yang diidentifikasi
    while (prev < std::min(step, numTrains) && hours[prev] < hour) {
        prev++;
    }

    // Cek apakah jam ada
    if (prev < numTrains && hours[prev] == hour) {
        std::cout << "Departure hour " << hour << " found. Here is the schedule:\n";

        // Traverse queue mingguan dan menampilkan kereta yang sesuai dengan jam
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

    delete[] hours;  //Membuang memori yang dialokasikan secara dinamis
}


void badCharHeuristic(const std::string& trainName, int badChar[256]) {
    // Inisialisasi semua kemunculan sebagai -1 (karakter tidak ada dalam pola)
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    // Memenuhi kemunculan aktual dari setiap karakter dalam pola
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
        Node* temp = currentDay->head;  // Memulai dari kereta pertama hari itu
        while (temp != nullptr) {
            int m = targetName.size();
            int n = temp->trainName.size();

            int badChar[256];
            badCharHeuristic(targetName, badChar);

            int shift = 0;  // Memindah pola terhadap teks
            while (shift <= (n - m)) {
                int j = m - 1;

                // Mengurangi indeks j pola ketika karakter pola dan teks cocok
                while (j >= 0 && targetName[j] == temp->trainName[shift + j]) {
                    j--;
                }

                // Jika pola cocok dengan substring teks
                if (j < 0) {
                    std::cout << "Train Name \"" << targetName << "\" found on " << currentDay->dayName << ".\n";
                    std::cout << "Details:\n";
                    std::cout << "  Train ID: " << temp->trainID << "";
                    std::cout << "  Train Name: " << temp->trainName << "";
                    std::cout << "  Destination: " << temp->destination << "";
                    std::cout << "  Departure Hour: " << temp->hour << "\n";
                    found = true;
                    break;
                } else {
                    // menggeser pola sehingga karakter buruk dalam teks sejajar dengan kemunculan terakhirnya dalam pola
                    shift += std::max(1, j - badChar[(int)temp->trainName[shift + j]]);
                }
            }

            if (found) break;
            temp = temp->next;  // Pindah ke kereta berikutnya
        }

        if (found) break;
        currentDay = currentDay->next;  // Pindah ke jadwal hari berikutnya
    }

    if (!found) {
        std::cout << "Train Name \"" << targetName << "\" not found in the weekly schedule.\n";
    }
}