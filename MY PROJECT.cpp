#include <iostream>
#include <string>
using namespace std;

// ==========================================
// BASE CLASS: Timber
// ==========================================
class Timber {
protected:
    string timberID;
    string treeType;
    int quantity;
    float unitPrice;

public:
    // Default constructor
    Timber() {
        timberID = "N/A";
        treeType = "Unknown";
        quantity = 0;
        unitPrice = 0.0;
    }

    // Parameterized constructor
    Timber(string id, string type, int qty, float price) {
        timberID = id;
        treeType = type;
        quantity = qty;
        unitPrice = price;
    }

    // Virtual destructor
    virtual ~Timber() {
    }

    // Function overloading
    void setDetails(string id, string type, int qty, float price) {
        timberID = id;
        treeType = type;
        quantity = qty;
        unitPrice = price;
    }

    void setDetails(string id, string type) {
        timberID = id;
        treeType = type;
        quantity = 0;
        unitPrice = 0.0;
    }

    // Getters
    string getTimberID() {
        return timberID;
    }

    int getQuantity() {
        return quantity;
    }

    float getUnitPrice() {
        return unitPrice;
    }

    // Virtual functions
    virtual float calculateTotalCost() {
        return quantity * unitPrice;
    }

    virtual void display() {
        cout << "Timber ID: " << timberID << endl;
        cout << "Tree Type: " << treeType << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Unit Price: " << unitPrice << endl;
    }

    // Operator overloading
    int operator+(Timber& other) {
        return this->quantity + other.quantity;
    }
};

// ==========================================
// DERIVED CLASS: Softwood
// ==========================================
class Softwood : public Timber {
private:
    string usage;

public:
    Softwood() : Timber() {
        usage = "General";
    }

    Softwood(string id, string type, int qty, float price, string use)
        : Timber(id, type, qty, price) {
        usage = use;
    }

    ~Softwood() {
    }

    void setSoftwoodDetails(string id, string type, int qty, float price, string use) {
        setDetails(id, type, qty, price);
        usage = use;
    }

    float calculateTotalCost() override {
        return quantity * unitPrice * 0.95; // 5% discount
    }

    void display() override {
        Timber::display();
        cout << "Category: Softwood" << endl;
        cout << "Usage: " << usage << endl;
        cout << "Total Cost: " << calculateTotalCost() << endl;
    }
};

// ==========================================
// DERIVED CLASS: Hardwood
// ==========================================
class Hardwood : public Timber {
private:
    string qualityGrade;

public:
    Hardwood() : Timber() {
        qualityGrade = "Standard";
    }

    Hardwood(string id, string type, int qty, float price, string grade)
        : Timber(id, type, qty, price) {
        qualityGrade = grade;
    }

    ~Hardwood() {
    }

    void setHardwoodDetails(string id, string type, int qty, float price, string grade) {
        setDetails(id, type, qty, price);
        qualityGrade = grade;
    }

    float calculateTotalCost() override {
        return quantity * unitPrice * 1.10; // 10% premium
    }

    void display() override {
        Timber::display();
        cout << "Category: Hardwood" << endl;
        cout << "Quality Grade: " << qualityGrade << endl;
        cout << "Total Cost: " << calculateTotalCost() << endl;
    }
};

// ==========================================
// DERIVED CLASS: ProcessedTimber
// ==========================================
class ProcessedTimber : public Timber {
private:
    string treatmentType;

public:
    ProcessedTimber() : Timber() {
        treatmentType = "Untreated";
    }

    ProcessedTimber(string id, string type, int qty, float price, string treatment)
        : Timber(id, type, qty, price) {
        treatmentType = treatment;
    }

    ~ProcessedTimber() {
    }

    void setProcessedDetails(string id, string type, int qty, float price, string treatment) {
        setDetails(id, type, qty, price);
        treatmentType = treatment;
    }

    float calculateTotalCost() override {
        return quantity * unitPrice * 1.20; // 20% processing charge
    }

    void display() override {
        Timber::display();
        cout << "Category: Processed Timber" << endl;
        cout << "Treatment Type: " << treatmentType << endl;
        cout << "Total Cost: " << calculateTotalCost() << endl;
    }
};

// ==========================================
// FUNCTION PROTOTYPES
// ==========================================
void showSalesSummary(float sales[3][7], int rows, int cols);

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    const int MAX = 10;

    // Single-dimensional arrays of objects
    Softwood softwoods[MAX];
    Hardwood hardwoods[MAX];
    ProcessedTimber processed[MAX];

    // Pointers to arrays of objects
    Softwood* softPtr = softwoods;
    Hardwood* hardPtr = hardwoods;
    ProcessedTimber* procPtr = processed;

    int softCount = 0;
    int hardCount = 0;
    int procCount = 0;

    // 2D array for weekly sales summary [3 categories][7 days]
    float weeklySales[3][7] = {0};

    int choice;

    do {
        cout << "\n==================================================" << endl;
        cout << "      SMART TIMBER YARD MANAGEMENT SYSTEM" << endl;
        cout << "==================================================" << endl;
        cout << "1. Add Softwood Record" << endl;
        cout << "2. Add Hardwood Record" << endl;
        cout << "3. Add Processed Timber Record" << endl;
        cout << "4. View All Timber Records" << endl;
        cout << "5. Search Timber by ID" << endl;
        cout << "6. Show Weekly Sales Summary (2D Array)" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                try {
                    if (softCount >= MAX) {
                        throw "Softwood storage is full!";
                    }

                    string id, type, use;
                    int qty;
                    float price;
                    int day;

                    cout << "\nEnter Softwood Details" << endl;
                    cout << "Timber ID: ";
                    cin >> id;

                    cout << "Tree Type: ";
                    cin >> type;

                    cout << "Quantity: ";
                    cin >> qty;

                    if (qty < 0) {
                        throw "Quantity cannot be negative!";
                    }

                    cout << "Unit Price: ";
                    cin >> price;

                    if (price < 0) {
                        throw "Unit price cannot be negative!";
                    }

                    cout << "Usage: ";
                    cin >> use;

                    cout << "Enter sale day (1-7): ";
                    cin >> day;

                    if (day < 1 || day > 7) {
                        throw "Invalid day! Please enter between 1 and 7.";
                    }

                    softPtr[softCount].setSoftwoodDetails(id, type, qty, price, use);

                    // Using pointer + polymorphism
                    Timber* t = &softPtr[softCount];
                    weeklySales[0][day - 1] += t->calculateTotalCost();

                    softCount++;
                    cout << "Softwood record added successfully!" << endl;
                }
                catch (const char* msg) {
                    cout << "Exception: " << msg << endl;
                }
                break;
            }

            case 2: {
                try {
                    if (hardCount >= MAX) {
                        throw "Hardwood storage is full!";
                    }

                    string id, type, grade;
                    int qty;
                    float price;
                    int day;

                    cout << "\nEnter Hardwood Details" << endl;
                    cout << "Timber ID: ";
                    cin >> id;

                    cout << "Tree Type: ";
                    cin >> type;

                    cout << "Quantity: ";
                    cin >> qty;

                    if (qty < 0) {
                        throw "Quantity cannot be negative!";
                    }

                    cout << "Unit Price: ";
                    cin >> price;

                    if (price < 0) {
                        throw "Unit price cannot be negative!";
                    }

                    cout << "Quality Grade: ";
                    cin >> grade;

                    cout << "Enter sale day (1-7): ";
                    cin >> day;

                    if (day < 1 || day > 7) {
                        throw "Invalid day! Please enter between 1 and 7.";
                    }

                    hardPtr[hardCount].setHardwoodDetails(id, type, qty, price, grade);

                    // Using pointer + polymorphism
                    Timber* t = &hardPtr[hardCount];
                    weeklySales[1][day - 1] += t->calculateTotalCost();

                    hardCount++;
                    cout << "Hardwood record added successfully!" << endl;
                }
                catch (const char* msg) {
                    cout << "Exception: " << msg << endl;
                }
                break;
            }

            case 3: {
                try {
                    if (procCount >= MAX) {
                        throw "Processed timber storage is full!";
                    }

                    string id, type, treatment;
                    int qty;
                    float price;
                    int day;

                    cout << "\nEnter Processed Timber Details" << endl;
                    cout << "Timber ID: ";
                    cin >> id;

                    cout << "Tree Type: ";
                    cin >> type;

                    cout << "Quantity: ";
                    cin >> qty;

                    if (qty < 0) {
                        throw "Quantity cannot be negative!";
                    }

                    cout << "Unit Price: ";
                    cin >> price;

                    if (price < 0) {
                        throw "Unit price cannot be negative!";
                    }

                    cout << "Treatment Type: ";
                    cin >> treatment;

                    cout << "Enter sale day (1-7): ";
                    cin >> day;

                    if (day < 1 || day > 7) {
                        throw "Invalid day! Please enter between 1 and 7.";
                    }

                    procPtr[procCount].setProcessedDetails(id, type, qty, price, treatment);

                    // Using pointer + polymorphism
                    Timber* t = &procPtr[procCount];
                    weeklySales[2][day - 1] += t->calculateTotalCost();

                    procCount++;
                    cout << "Processed timber record added successfully!" << endl;
                }
                catch (const char* msg) {
                    cout << "Exception: " << msg << endl;
                }
                break;
            }

            case 4: {
                cout << "\n=============== ALL TIMBER RECORDS ===============" << endl;

                if (softCount == 0 && hardCount == 0 && procCount == 0) {
                    cout << "No records available." << endl;
                    break;
                }

                // while loop for softwood
                if (softCount > 0) {
                    cout << "\n--- SOFTWOOD RECORDS ---" << endl;
                    int i = 0;
                    while (i < softCount) {
                        cout << "\nRecord " << i + 1 << endl;
                        softPtr[i].display();
                        i++;
                    }
                }

                // for loop for hardwood
                if (hardCount > 0) {
                    cout << "\n--- HARDWOOD RECORDS ---" << endl;
                    for (int i = 0; i < hardCount; i++) {
                        cout << "\nRecord " << i + 1 << endl;
                        hardPtr[i].display();
                    }
                }

                // do-while loop for processed timber
                if (procCount > 0) {
                    cout << "\n--- PROCESSED TIMBER RECORDS ---" << endl;
                    int i = 0;
                    do {
                        cout << "\nRecord " << i + 1 << endl;
                        procPtr[i].display();
                        i++;
                    } while (i < procCount);
                }

                // Operator overloading demonstration
                if (softCount >= 2) {
                    cout << "\nCombined Quantity of First Two Softwood Records: "
                         << (softPtr[0] + softPtr[1]) << endl;
                }

                break;
            }

            case 5: {
                string searchID;
                bool found = false;

                cout << "\nEnter Timber ID to search: ";
                cin >> searchID;

                // Search in Softwood
                for (int i = 0; i < softCount; i++) {
                    if (softPtr[i].getTimberID() == searchID) {
                        cout << "\nRecord Found in Softwood!" << endl;
                        softPtr[i].display();
                        found = true;
                        break;
                    }
                }

                // Search in Hardwood
                if (!found) {
                    for (int i = 0; i < hardCount; i++) {
                        if (hardPtr[i].getTimberID() == searchID) {
                            cout << "\nRecord Found in Hardwood!" << endl;
                            hardPtr[i].display();
                            found = true;
                            break;
                        }
                    }
                }

                // Search in Processed Timber
                if (!found) {
                    for (int i = 0; i < procCount; i++) {
                        if (procPtr[i].getTimberID() == searchID) {
                            cout << "\nRecord Found in Processed Timber!" << endl;
                            procPtr[i].display();
                            found = true;
                            break;
                        }
                    }
                }

                // Ternary operator
                cout << (found ? "Search completed successfully." : "No timber record found.") << endl;

                break;
            }

            case 6: {
                showSalesSummary(weeklySales, 3, 7);
                break;
            }

            case 7:
                cout << "\nExiting system... Thank you!" << endl;
                break;

            default:
                cout << "\nInvalid choice! Please select between 1 and 7." << endl;
        }

    } while (choice != 7);

    return 0;
}

// ==========================================
// FUNCTION TO DISPLAY 2D ARRAY SALES SUMMARY
// ==========================================
void showSalesSummary(float sales[3][7], int rows, int cols) {
    string categories[3] = {"Softwood", "Hardwood", "Processed"};

    cout << "\n========== WEEKLY SALES SUMMARY ==========" << endl;
    cout << "Days: 1 2 3 4 5 6 7" << endl;

    for (int i = 0; i < rows; i++) {
        cout << categories[i] << ": ";
        for (int j = 0; j < cols; j++) {
            cout << sales[i][j] << " ";
        }
        cout << endl;
    }
}
