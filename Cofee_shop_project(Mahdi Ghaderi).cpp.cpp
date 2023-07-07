#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//class of warehouse stock
class warehouse_stock
{
public:
    string name;
    int quantity;
};

//class of coffee shop products
class Product
{
public:
    int id;
    string name;
    double price;
};

//Cold drinks class
class cold_drink
{
private:
    string name;
    int price;
    int quantity;

public:
    cold_drink(string n, int p, int q)
    {
        name = n;
        price = p;
        quantity = q;
    }
    int total_price()
    {
        return price * quantity;
    }
};

//Hot drink class
class hot_drink {
private: 
    string name;
    int price;
    int quantity;
public:
    hot_drink(string n, int p, int q)
    {
        name = n;
        price = p;
        quantity = q;
    }
    int total_price()
    {
        return price * quantity;
    }
};

//Food class
class food {
private:
    string name;
    int price;
    int quantity;
public:
    food(string n, int p, int q)
    {
        name = n;
        price = p;
        quantity = q;
    }
    int total_price()
    {
        return price * quantity;
    }
};


int main()
{
    
    ofstream income("income.txt", ios_base::app);

    string date;

    cout << "Enter today date: ";
    cin >> date;

    income << endl << "------" + date + "------" << endl;

    // An array of products:
    Product products[] = {
        {1, "Coldbrew", 6},
        {2, "Iced Latte", 5.5},
        {3, "Chocolate shake", 7},
        {4, "Chic Nutella", 7.5},
        {5, "Strawberry Shake", 7},
        {6, "Vanilla chic", 7},
        {7, "Mojito", 8.5},
        {8, "Espresso coffee", 5},
        {9, "Turk coffee", 4.5},
        {10, "Cappuccino", 5},
        {11, "Mocha", 5.5},
        {12, "Hot chocolate", 6},
        {13, "Tea", 3},
        {14, "Pasta", 19},
        {15, "Burger", 22},
        {16, "Potato", 15},
        {17, "Caesar salad", 18},
        {18, "Pizza", 23} 
    };

    // Writing products to a binary file:

    ofstream store1("products.bin", ios::binary);
    if (store1.is_open())
    {
        store1.write(reinterpret_cast<const char*>(products), sizeof(products));
        store1.close();
    }
    else
        cout << "File is not opened!";

    // Reading products from the binary file:

    ifstream store2("products.bin", ios::binary);
    if (store2.is_open())
    {
        Product readproducts[sizeof(products) / sizeof(Product)];
        store2.read(reinterpret_cast<char*>(readproducts), sizeof(readproducts));
        store2.close();

        // print of the products:

        cout << "Welcome to our Coffee Shop!" << endl;
        cout << "The menu: " << endl;
        for (const Product& product : readproducts)
        {
            cout << "ID: " << product.id << endl;
            cout << "Name: " << product.name << endl;
            cout << "Price: " << product.price << endl;
            cout << "--------------------------------" << endl;
        }
    }

    // An array of warehouse_stock:

    warehouse_stock stock[] = {
        {"Coldbrew", 25},
        {"Iced Latte", 25},
        {"Chocolate shake", 25},
        {"Chic Nutella", 25},
        {"Strawberry Shake", 25},
        {"Vanilla chic", 25},
        {"Mojito", 25},
        {"Espresso coffee", 25},
        {"Turk coffee", 25},
        {"Cappuccino", 25},
        {"Mocha", 25},
        {"Hot chocolate", 25},
        {"Tea", 25},
        {"Pasta", 25},
        {"Burger", 25},
        {"Potato", 25},
        {"Caesar salad", 25},
        {"Pizza", 25} };

    // writing stock to the binary file:
    ofstream stock1("stock.bin", ios::binary);
    if (stock1.is_open())
    {
        stock1.write(reinterpret_cast<const char*>(stock), sizeof(stock));
        stock1.close();
    }
    else
        cout << "File is not opened!";

    // Get the number of customers:
    int num_customers;
    cout << "Please enter the number of customers: ";
    cin >> num_customers;

    // Process each customer's order:
    for (int i = 0; i < num_customers; i++)
    {
        // Get customer's name and phone number:
        string customer_name;
        string phone_number;
        cout << "Please enter your name: " << endl;
        cin >> customer_name;
        cout << "Please enter your phone number :" << endl;
        cin >> phone_number;

        // Open the customer_info file for writing
        ofstream customer_info("customer_info.txt", ios_base::app);

        // Check if the file is open before writing to it
        if (customer_info.is_open())
        {
            // Write the customer's name and phone number to the file
            customer_info << endl
                << "customer_name: " << customer_name << endl;
            customer_info << "phone_number: " << phone_number << endl;
            customer_info << "----------------------------------";
            customer_info.close();
        }
        else
            cout << "File is not opened!";

        // Create an array to store the customer's order:
        int order[18] = { 0 };

        // Get the customer's order:
        int choice;
        do
        {
            cout << "Please enter your order (0 to finish): ";
            cin >> choice;
            if (choice != 0)
            {
                int quantity;
                cout << "Please enter the quantity: ";
                cin >> quantity;
                order[choice - 1] = quantity;
            }
        } while (choice != 0);

        // Display the customer's order and total price:
        cout << "--------------------------" << endl;
        cout << "Customer's Order:" << endl;
        double total_price = 0;
        for (int i = 0; i < 18; i++)
        {
            if (order[i] != 0)
            {
                cout << products[i].name << " x " << order[i] << endl;
                total_price += products[i].price * order[i];
            }
        }
        cout << "--------------------------" << endl;
        cout << "Total Price: " << total_price << "$" << endl;

        income << "Total price: " + customer_name + ": " << total_price << "$" << endl;
        for (int i = 0; i < 18; i++)
        {
            if (order[i] != 0)
            {
                income << products[i].name << " x " << order[i] << endl;
            }
        }
        income << endl;

        ofstream customer_bill(customer_name + "-invoice" + ".txt");
        if (customer_bill.is_open())
        {
            customer_bill << endl
                << "customer_name: " << customer_name << endl;
            customer_bill << "total: " << total_price << endl;
            customer_bill.close();
        }
        else
            cout << "File is not opened!";

        // Update the stock:
        for (int i = 0; i < 18; i++)
        {
            stock[i].quantity -= order[i];

            if (stock[i].quantity < 20)
            {
                cout << endl
                    << "The stock of this product is less than 20 pieces! " << endl;
            }
        }

        // Writing the updated stock to the binary file:
        ofstream stock3("stock.bin", ios::binary);
        if (stock3.is_open())
        {
            stock3.write(reinterpret_cast<const char*>(stock), sizeof(stock));
            stock3.close();
        }
        else
            cout << "File is not opened!";

        // Write the order to a text file:
        ofstream orders("orders.txt", ios::app);
        if (orders.is_open())
        {
            orders << "Customer Name: " << customer_name << endl;
            orders << "Phone Number: " << phone_number << endl;
            orders << "Total Price : $" << total_price << endl;
            orders << "-----------------------------------";
            orders.close();
        }
        else
            cout << "File is not opened!";
    }
    // Open the customer_info file for reading
    ifstream customer_info("customer_info.txt");

    // Check if the file is open before reading from it
    if (customer_info.is_open())
    {
        string s;
        while (getline(customer_info, s))
        {
            cout << s << endl;
        }
        customer_info.close();
    }
    else
        cout << "File is not opened!";
}










