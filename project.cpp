#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <sstream>

using namespace std;

struct Product {
    string name;
    string category;
    double price;
    double rating;

    // Default constructor
    Product() : name(""), category(""), price(0.0), rating(0.0) {}

    // Parameterized constructor
    Product(string n, string c, double p, double r) : name(n), category(c), price(p), rating(r) {}
};

// Function to display products
void displayProducts(const vector<Product>& products) {
    for (const auto& product : products) {
        cout << "-----------------------" << endl;
        cout << "Name: " << product.name << endl;
        cout << "Price: $" << product.price << endl;
        cout << "Rating: " << product.rating << " stars" << endl;
        cout << "Category: " << product.category << endl;
    }
    cout << "-----------------------" << endl;
}

// Comparison functions for merge sort
bool compareByPrice(const Product& p1, const Product& p2) {
    return p1.price < p2.price;
}

bool compareByRating(const Product& p1, const Product& p2) {
    return p1.rating > p2.rating;
}

// Merge function used in Merge Sort
void merge(vector<Product>& products, int left, int mid, int right, bool sortByPrice) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Product> leftArray(n1);
    vector<Product> rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = products[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = products[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (sortByPrice ? (leftArray[i].price <= rightArray[j].price) : (leftArray[i].rating >= rightArray[j].rating)) {
            products[k] = leftArray[i];
            i++;
        } else {
            products[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        products[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        products[k] = rightArray[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(vector<Product>& products, int left, int right, bool sortByPrice) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(products, left, mid, sortByPrice);
    mergeSort(products, mid + 1, right, sortByPrice);
    merge(products, left, mid, right, sortByPrice);
}

// Binary Search for lower bound
int binarySearchLowerBound(vector<Product>& products, double targetPrice) {
    int left = 0;
    int right = products.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].price >= targetPrice) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// Binary Search for upper bound
int binarySearchUpperBound(vector<Product>& products, double targetPrice) {
    int left = 0;
    int right = products.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].price <= targetPrice) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

// Function to search products by name (case-insensitive)
vector<Product> searchProductsByName(const vector<Product>& products, const string& searchTerm) {
    vector<Product> result;
    string lowerSearchTerm = searchTerm;
    transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);

    for (const auto& product : products) {
        string lowerName = product.name;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (lowerName.find(lowerSearchTerm) != string::npos) {
            result.push_back(product);
        }
    }
    return result;
}

// Function to display products within a price range
void displayProductsInRange(vector<Product>& products, double lowerPrice, double upperPrice) {
    int lowerIndex = binarySearchLowerBound(products, lowerPrice);
    int upperIndex = binarySearchUpperBound(products, upperPrice);

    if (lowerIndex <= upperIndex) {
        cout << "Products in the price range [" << lowerPrice << ", " << upperPrice << "]:" << endl;
        for (int i = lowerIndex; i <= upperIndex; ++i) {
            cout << products[i].name << " - Price: " << products[i].price << ", Rating: " << products[i].rating << endl;
        }
    } else {
        cout << "No products found in the given price range." << endl;
    }
}

void displayProductsWithRating(vector<Product>& products, double reqRating){
    for(Product p : products){
        if(p.rating>=reqRating){
            cout << p.name << " - Price: " << p.price << ", Rating: " << p.rating << endl;
        }
    }
}

vector<Product> searchProductsByCategory(const vector<Product>& products, const string& category) {
    vector<Product> result;
    string lowerCategory = category;
    transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(), ::tolower);

    for (const auto& product : products) {
        string lowerProductCategory = product.category;
        transform(lowerProductCategory.begin(), lowerProductCategory.end(), lowerProductCategory.begin(), ::tolower);

        if (lowerProductCategory == lowerCategory) {
            result.push_back(product);
        }
    }
    return result;
}

// Heapify function for heap sort
void heapify(vector<Product>& products, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < n && products[left].price > products[largest].price) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && products[right].price > products[largest].price) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(products[i], products[largest]);

        // Recursively heapify the affected sub-tree
        heapify(products, n, largest);
    }
}

// Heap sort function
void heapSort(vector<Product>& products) {
    int n = products.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(products, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i >= 0; i--) {
        swap(products[0], products[i]);

        // Call max heapify on the reduced heap
        heapify(products, i, 0);
    }
}

vector<Product> readFromCSV(const string& filename) {
    vector<Product> products;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return products;
    }

    string line;
    bool firstLine = true; // Skip the header

    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // Skip the header line
        }

        stringstream ss(line);
        string name, category, priceStr, ratingStr;
        double price, rating;

        // Read each attribute separated by a comma
        if (getline(ss, name, ',') && getline(ss, category, ',') &&
            getline(ss, priceStr, ',') && getline(ss, ratingStr, ',')) {
            price = stod(priceStr);
            rating = stod(ratingStr);

            // Create a Product instance and add it to the vector
            products.emplace_back(name, category, price, rating);
        }
    }

    file.close();
    return products;
}

int main() {
    vector<Product> products;
    const string filename = "catalogue.csv";
    products = readFromCSV(filename);

    // Search functionality
    string searchTerm;
    search:
    cout << "Enter the product name (search term): ";
    //cin.ignore();  // To handle the newline character from previous input
    getline(cin, searchTerm);

    vector<Product> foundProducts = searchProductsByName(products, searchTerm);
    vector<Product> finalProducts;

    if (foundProducts.empty()) {
    //if products not found by name then search for category
        cout << "Products found for " << searchTerm << endl;
        finalProducts = searchProductsByCategory(products, searchTerm);
        displayProducts(finalProducts);
    } else {
        cout << "Products matching \"" << searchTerm << "\":" << endl;
        for (const auto& p : foundProducts) {
            cout << p.name << " - Price: " << p.price << ", Rating: " << p.rating << endl;
        }
        finalProducts=foundProducts;
    }

    string sortChoice;
    cout << "Do you want to sort products? (yes/no): ";
    cin >> sortChoice;

    if (sortChoice == "yes" || sortChoice == "YES") {
        int choice;
        cout << "Do you want to sort products?\n1. Sort by Price\n2. Sort by Rating\n";
        repeat:
            cout << "Enter your choice (1-2): ";
            cin >> choice;

            switch (choice) {
                case 1:{
                    heapSort(finalProducts);
                    cout << "\nProducts sorted by Price:\n";
                    displayProducts(finalProducts);
                    string rangeChoice;
                    cout << "Do you want to set a price range? (yes/no): ";
                    cin >> rangeChoice;

                    if (rangeChoice == "yes" || rangeChoice == "YES") {
                        double lowerPrice, upperPrice;
                        cout << "Enter the price range (lower and upper values): ";
                        cin >> lowerPrice >> upperPrice;
                        displayProductsInRange(finalProducts, lowerPrice, upperPrice);
                    } 
                    else {
                        string ask;
                        cout<<"Do you want to exit?(yes/no)";
                        cin>>ask;
                        if(ask=="yes")
                        exit(0);
                        else
                        goto search;
                    } 
                    break;
                }
                case 2:{
                    heapSort(finalProducts);
                    cout << "\nProducts sorted by Rating:\n";
                    displayProducts(finalProducts);
                    string minRating;
                    cout << "Do you want to set a minimum rating criteria? (yes/no): ";
                    cin >> minRating;

                    if (minRating == "yes" || minRating == "YES") {
                        double reqRating;
                        cout << "Enter the minimum acceptable rating for the product: ";
                        cin >> reqRating;
                        displayProductsWithRating(finalProducts,reqRating);
                    } 
                    else {
                        string ask;
                        cout<<"Do you want to exit?(y/n)";
                        cin>>ask;
                        if(ask=="yes")
                        exit(0);
                        else
                        goto search;
                    }
                    break;
                }
                default:
                    cout << "Invalid choice.\n";
                    goto repeat;
                
            }
    }
    else{
        goto search;
    }
    
    char ch;
    cout<<"press any key to exit"<<endl;
    cin>>ch;
    // Ask the user if they want to set a price range
    

    return 0;
}