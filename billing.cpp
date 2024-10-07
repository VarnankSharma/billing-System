#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <windows.h>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) {
        Item = item;
    }
    void setRate(int rate) {
        Rate = rate;
    }
    void setQuant(int quant) {
        Quantity = quant;
    }
    string getItem() {
        return Item;
    }
    int getRate() {
        return Rate;
    }
    int getQuant() {
        return Quantity;
    }
};

void drawText(int x, int y, const char* text) {
    outtextxy(x, y, (char*)text); // Cast const char* to char*
}

void addItem(Bill b) {
    bool close = false;
    while (!close) {
        int choice;
        cleardevice();
        drawText(100, 100, "1. Add Item");
        drawText(100, 150, "2. Close");
        drawText(100, 200, "Enter Choice: ");
        cin >> choice;

        if (choice == 1) {
            cleardevice();
            string item;
            int rate, quant;
            drawText(100, 100, "Enter item Name: ");
            cin >> item;
            b.setItem(item);
            drawText(100, 150, "Enter item Rate: ");
            cin >> rate;
            b.setRate(rate);
            drawText(100, 200, "Enter item Quantity: ");
            cin >> quant;
            b.setQuant(quant);

            ofstream out("C:/Users/hp/Desktop/Billing System/bill.txt",ios::app);
            if (!out) {
                drawText(100, 250, "Error: File Can't Open!");
            } else {
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl << endl;
            }
            out.close();
            drawText(100, 250, "Entered Successfully");
            delay(3000);
        } else if (choice == 2) {
            cleardevice();
            close = true;
            drawText(100, 100, "Back to Main Menu");
            delay(3000);
        }
    }
}

void printBill() {
    cleardevice();
    int count = 0;
    bool close = false;
    while (!close) {
        cleardevice();
        int choice;
        drawText(100, 100, "1. Add Item");
        drawText(100, 150, "2. Close");
        drawText(100, 200, "Enter Choice: ");
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            drawText(100, 100, "Enter Item: ");
            cin >> item;
            drawText(100, 150, "Enter Quantity: ");
            cin >> quant;

            ifstream in("C:/Users/hp/Desktop/Billing System/bill.txt");
            ofstream out("C:/Users/hp/Desktop/Billing System/bill temp.txt");

            string line;
            bool found = false;
            while (getline(in, line)) {
                stringstream ss;
                ss << line;
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        drawText(100, 200, "Item | Rate | Quantity | Amount");
                        string result = itemName + "\t" + to_string(itemRate) + "\t" + to_string(quant) + "\t" + to_string(amount);
                        drawText(100, 250, result.c_str());
                        int newQuant = itemQuant - quant;
                        itemQuant = newQuant;
                        count += amount;

                        out << itemName << ":" << itemRate << ":" << itemQuant << endl << endl;
                    } else {
                        drawText(100, 300, ("Sorry, " + item + " Ended!").c_str());
                    }
                } else {
                    out << line << endl;
                }
            }

            if (!found) {
                drawText(100, 350, "Item Not Available!");
            }

            out.close();
            in.close();
            remove("bill.txt");
            rename("bill_temp.txt", "bill.txt");
        } else if (choice == 2) {
            close = true;
            drawText(100, 300, "Counting Total Bill");
            delay(3000);
        }
    }
    cleardevice();
    string totalBill = "Total Bill: " + to_string(count);
    drawText(100, 100, totalBill.c_str());
    drawText(100, 150, "Thanks for shopping!");
    delay(5000);
}

int main() {
    // Initialize graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");  // Auto-detect and initialize graphics mode

    Bill b;
    bool exit = false;
    while (!exit) {
        cleardevice();
        int val;
        drawText(100, 100, "Welcome To SUPER Market Billing System");
        drawText(100, 150, "**************************************");
        drawText(100, 200, "1. Add Item");
        drawText(100, 250, "2. Print Bill");
        drawText(100, 300, "3. Exit");
        drawText(100, 350, "Enter Choice: ");
        cin >> val;

        if (val == 1) {
            cleardevice();
            addItem(b);
            delay(3000);
        } else if (val == 2) {
            printBill();
        } else if (val == 3) {
            cleardevice();
            exit = true;
            drawText(100, 100, "Good Luck!");
            delay(5000);
        }
    }

    closegraph();
    return 0;
}
