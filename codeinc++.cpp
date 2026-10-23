#include <iostream>
#include <string>
using namespace std;

class Customer
{
private:
    string name;
    string category;
    int tickets;
    double price;

public:
    Customer(string n, string c, int t)
    {
        name = n;
        category = c;
        tickets = t;

        if (category == "Silver")
            price = 150;
        else if (category == "Gold")
            price = 250;
        else
            price = 400;
    }

    double calculateBill()
    {
        return price * tickets;
    }

    double applyDiscount(double bill)
    {
        return bill * 0.90;
    }

    double calculateServiceCharge(double bill)
    {
        if (bill > 1000)
            return bill * 0.05;
        return 0;
    }

    void displayBill()
    {
        double bill = calculateBill();
        double discount = 0;
        double serviceCharge;

        // Assume customer is a senior citizen
        discount = bill * 0.10;

        double afterDiscount = bill - discount;
        serviceCharge = calculateServiceCharge(afterDiscount);

        double finalBill = afterDiscount + serviceCharge;

        cout << "\n----- CINEMA BILL -----\n";
        cout << "Customer Name : " << name << endl;
        cout << "Ticket Category : " << category << endl;
        cout << "Number of Tickets : " << tickets << endl;
        cout << "Price per Ticket : Rs. " << price << endl;
        cout << "Basic Bill : Rs. " << bill << endl;
        cout << "Senior Citizen Discount : Rs. " << discount << endl;
        cout << "Service Charge : Rs. " << serviceCharge << endl;
        cout << "Final Bill : Rs. " << finalBill << endl;
    }
};

int main()
{
    Customer c("Sudha", "Gold", 5);
    c.displayBill();

    return 0;
}