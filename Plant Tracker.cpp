#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ---------------- STRUCT ---------------- //
struct PlantData {
    string Category;
    float Water;
    float Sunlight;
    string Feedback;
    string Recommendation;
};

// ---------------- GLOBAL VARIABLES ---------------- //

// Equivalent to Python Dictionary
unordered_map<string, string> Plant_Categories = {

    // High Sun / Low Water
    {"Aloe Vera", "High Sun / Low Water"},
    {"Cactus", "High Sun / Low Water"},
    {"Snake Plant", "High Sun / Low Water"},
    {"Jade Plant", "High Sun / Low Water"},
    {"Echeveria", "High Sun / Low Water"},
    {"Sedum", "High Sun / Low Water"},
    {"Agave", "High Sun / Low Water"},
    {"Burro's Tail", "High Sun / Low Water"},

    // High Sun / High Water
    {"Tomato", "High Sun / High Water"},
    {"Cucumber", "High Sun / High Water"},
    {"Basil", "High Sun / High Water"},
    {"Eggplant", "High Sun / High Water"},
    {"Bell Pepper", "High Sun / High Water"},
    {"Zucchini", "High Sun / High Water"},
    {"Squash", "High Sun / High Water"},
    {"Water Spinach (Kangkong)", "High Sun / High Water"},

    // Low Sun / Low Water
    {"ZZ Plant", "Low Sun / Low Water"},
    {"Pothos", "Low Sun / Low Water"},
    {"Peace Lily", "Low Sun / Low Water"},
    {"Cast Iron Plant", "Low Sun / Low Water"},
    {"Rubber Plant", "Low Sun / Low Water"},
    {"Chinese Evergreen", "Low Sun / Low Water"},
    {"Dracaena", "Low Sun / Low Water"},
    {"Philodendron", "Low Sun / Low Water"},

    // Low Sun / High Water
    {"Fern", "Low Sun / High Water"},
    {"Calathea", "Low Sun / High Water"},
    {"Spider Plant", "Low Sun / High Water"},
    {"Mint", "Low Sun / High Water"},
    {"Parsley", "Low Sun / High Water"},
    {"Cilantro", "Low Sun / High Water"},
    {"Boston Fern", "Low Sun / High Water"},
    {"Taro (Gabi)", "Low Sun / High Water"}
};

// Stores all plant records
unordered_map<string, PlantData> Plants;

// ---------------- CATEGORY FUNCTIONS ---------------- //

string High_Sun_Low_Water(float Water, float Sun) {

    if (Sun >= 8 && Water >= 0.2 && Water <= 0.5) {
        return "Optimal Condition";
    }

    return "Needs Adjustment";
}

string High_Sun_High_Water(float Water, float Sun) {

    if (Sun >= 8 && Water >= 0.5 && Water <= 1.5) {
        return "Optimal Condition";
    }

    return "Needs Adjustment";
}

string Low_Sun_Low_Water(float Water, float Sun) {

    if (Sun >= 2 && Sun <= 4 &&
        Water >= 0.2 && Water <= 0.5) {

        return "Optimal Condition";
    }

    return "Needs Adjustment";
}

string Low_Sun_High_Water(float Water, float Sun) {

    if (Sun >= 2 && Sun <= 4 &&
        Water >= 0.5 && Water <= 1.5) {

        return "Optimal Condition";
    }

    return "Needs Adjustment";
}

// ---------------- EVALUATION ---------------- //

string Evaluate_Plant(string category,
                      float Water,
                      float Sun) {

    if (category == "High Sun / Low Water") {

        return High_Sun_Low_Water(Water, Sun);
    }

    else if (category == "High Sun / High Water") {

        return High_Sun_High_Water(Water, Sun);
    }

    else if (category == "Low Sun / Low Water") {

        return Low_Sun_Low_Water(Water, Sun);
    }

    else if (category == "Low Sun / High Water") {

        return Low_Sun_High_Water(Water, Sun);
    }

    return "Unknown Plant Category";
}

// ---------------- RECOMMENDATION ---------------- //

string get_recommendation(string category,
                          float water,
                          float sun) {

    string rec = "";

    // LOW WATER
    if (category.find("Low Water") != string::npos) {

        if (water < 0.2 || water > 0.5) {

            rec += "Recommended water is 0.2L to 0.5L\n";
        }
    }

    // HIGH WATER
    if (category.find("High Water") != string::npos) {

        if (water < 0.5 || water > 1.5) {

            rec += "Recommended water is 0.5L to 1.5L\n";
        }
    }

    // HIGH SUN
    if (category.find("High Sun") != string::npos) {

        if (sun < 8) {

            rec += "Increase sunlight to 8+ hours\n";
        }
    }

    // LOW SUN
    if (category.find("Low Sun") != string::npos) {

        if (sun < 2) {

            rec += "Increase sunlight to 2 hours\n";
        }

        else if (sun > 4) {

            rec += "Recommended sunlight is 2 to 4 hours\n";
        }
    }

    if (rec == "") {
        return "No changes needed";
    }

    return rec;
}

// ---------------- SUBMIT DATA ---------------- //

void submit_data() {

    string name;
    float water;
    float sun;

    cout << "\nEnter Plant Name: ";
    getline(cin, name);

    // Plant validation
    if (Plant_Categories.find(name) == Plant_Categories.end()) {

        cout << "Plant not found!\n";
        return;
    }

    cout << "Enter Water (L): ";
    cin >> water;

    cout << "Enter Sunlight Hours: ";
    cin >> sun;

    cin.ignore();

    string category = Plant_Categories[name];

    string feedback =
        Evaluate_Plant(category, water, sun);

    string recommendation =
        get_recommendation(category, water, sun);

    // Store data in unordered_map
    Plants[name] = {
        category,
        water,
        sun,
        feedback,
        recommendation
    };

    cout << "\n===== RESULT =====\n";

    cout << "Plant: " << name << endl;
    cout << "Category: " << category << endl;
    cout << "Feedback: " << feedback << endl;

    cout << "\nRecommendation:\n";
    cout << recommendation << endl;
}

// ---------------- VIEW ALL PLANTS ---------------- //

void view_plants() {

    if (Plants.empty()) {

        cout << "\nNo Plant Records Found.\n";
        return;
    }

    cout << "\n========== PLANT RECORDS ==========\n";

    for (auto& plant : Plants) {

        cout << "\nPlant Name: "
             << plant.first << endl;

        cout << "Category: "
             << plant.second.Category << endl;

        cout << "Water: "
             << plant.second.Water << "L\n";

        cout << "Sunlight: "
             << plant.second.Sunlight << " hrs\n";

        cout << "Feedback: "
             << plant.second.Feedback << endl;

        cout << "Recommendation: "
             << plant.second.Recommendation << endl;
    }
}

// ---------------- DELETE PLANT ---------------- //

void delete_plant() {

    string name;

    cout << "\nEnter plant name to delete: ";
    getline(cin, name);

    if (Plants.find(name) != Plants.end()) {

        Plants.erase(name);

        cout << "Plant deleted successfully.\n";
    }

    else {

        cout << "Plant not found in records.\n";
    }
}

// ---------------- VIEW CATEGORIES ---------------- //

void view_categories() {

    // Category -> vector of plants
    unordered_map<string, vector<string>> grouped;

    // Group plants
    for (auto& plant : Plant_Categories) {

        grouped[plant.second].push_back(plant.first);
    }

    cout << "\n========== CATEGORIES ==========\n";

    for (auto& category : grouped) {

        cout << "\n" << category.first << endl;

        cout << "-----------------------------\n";

        for (string plant : category.second) {

            cout << "• " << plant << endl;
        }
    }
}

// ---------------- MENU ---------------- //

void menu() {

    int choice;

    do {

        cout << "\n===== PLANT GROWTH TRACKER =====\n";

        cout << "1. Evaluate Plant\n";
        cout << "2. View All Plants\n";
        cout << "3. Delete Plant\n";
        cout << "4. View Categories\n";
        cout << "0. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice) {

            case 1:
                submit_data();
                break;

            case 2:
                view_plants();
                break;

            case 3:
                delete_plant();
                break;

            case 4:
                view_categories();
                break;

            case 0:
                cout << "Program Ended.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 0);
}

// ---------------- MAIN ---------------- //

int main() {

    menu();

    return 0;
}