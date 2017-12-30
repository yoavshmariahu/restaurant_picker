#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h> 

using namespace std;

// monkey text art
const string TEXTART = "              ┈┈╱▔▔▔▔▔╲┈┈┈HM┈HM\n              ┈╱┈┈╱▔╲╲╲▏┈┈┈HMMM\n              ╱┈┈╱━╱▔▔▔▔▔╲━╮┈┈\n              ▏┈▕┃▕╱▔╲╱▔╲▕╮┃┈┈\n              ▏┈▕╰━▏▊▕▕▋▕▕━╯┈┈\n              ╲┈┈╲╱▔╭╮▔▔┳╲╲┈┈┈\n              ┈╲┈┈▏╭━━━━╯▕▕┈┈┈\n              ┈┈╲┈╲▂▂▂▂▂▂╱╱┈┈┈\n              ┈┈┈┈▏┊┈┈┈┈┊┈┈┈╲┈\n              ┈┈┈┈▏┊┈┈┈┈┊▕╲┈┈╲\n              ┈╱▔╲▏┊┈┈┈┈┊▕╱▔╲▕\n              ┈▏ ┈┈┈╰┈┈┈┈╯┈┈┈▕▕\n              ┈╲┈┈┈╲┈┈┈┈╱┈┈┈╱┈╲\n              ┈┈╲┈┈▕▔▔▔▔▏┈┈╱╲╲╲▏\n              ┈╱▔┈┈▕┈┈┈┈▏┈┈▔╲▔▔\n              ┈╲▂▂▂╱┈┈┈┈╲▂▂▂╱┈\n";

// City mapping
enum City {
  mountain_view,
  sunnyvale,
  cupertino,
  san_jose,
  campbell,
  palo_alto,
  los_altos,
  saratoga,
  santa_clara,
  no_where
};
map<string, City> city_map = {
  {"MOUNTAIN VIEW", mountain_view},
  {"SUNNYVALE", sunnyvale},
  {"CUPERTINO", cupertino},
  {"SAN JOSE", san_jose},
  {"CAMPBELL", campbell},
  {"PALO ALTO", palo_alto},
  {"LOS ALTOS", los_altos},
  {"SARATOGA", saratoga},
  {"SANTA CLARA", santa_clara},
  {"NO WHERE", no_where}
};

// Origin mapping
enum Origin {
  japanese,
  korean,
  american,
  mexican,
  thai,
  fast_food,
  italian,
  greek,
  medeteranian,
  brunch,
  other_asian,
  other,
  none
};
map<string, Origin> origin_map = {
  {"JAPANESE", japanese},
  {"KOREAN", korean},
  {"AMERICAN", american},
  {"MEXICAN", mexican},
  {"THAI", thai},
  {"FAST FOOD", fast_food},
  {"ITALIAN", italian},
  {"GREEK", greek},
  {"MEDETERANIAN", medeteranian},
  {"BRUNCH", brunch},
  {"OTHERASIAN", other_asian},
  {"OTHER", other},
  {"NONE", none}
};

// Level mapping
enum Level {
  mama_huang,
  moderate,
  casual,
  no_class
};
map<string, Level> level_map = {
  {"MAMAHUANG", mama_huang},
  {"MODERATE", moderate},
  {"CASUAL", casual},
  {"NO CLASS", no_class}
};

// Option struct for menu option ordering
struct Option { char order; int selection; bool used; };

// Restaurant class for containing and retrieving restaurant data
class Restaurant {
  public:
    Restaurant(string name, City city, int price, Origin origin, Level level, bool filter = true) 
                : name_(name), city_(city), price_(price), origin_(origin), level_(level), filter_(filter) {}
    string to_string() {
      return name_ + "\n";
    }
    City get_city() {
      return city_;
    }
    int get_price() {
      return price_;
    }
    Origin get_origin() {
      return origin_;
    }
    Level get_level() {
      return level_;
    }
    bool get_filter() {
      return filter_;
    }
    void filter_out() {
      filter_ = false;
    }
  private:
    string name_;
    City city_;
    int price_;
    Origin origin_;
    Level level_;
    bool filter_;
};

// Print header of program
void print_header() {
  cout << "\n\n-----------------------------------------------"
       << "\n         WELCOME TO GLORIA AND YOAV'S \n         RESTAURANT PICKER HELPER!\n"
       << "-----------------------------------------------\n\n"
       << TEXTART << endl << endl;
}

// Print menu and prompt user for selection
// return char of corresponding selection
char menu(vector<Option>& options_arr) {
  cout << "              What would you like to do?\n";
  if (!options_arr[0].used) {
    cout << "              " << options_arr[0].selection << ". Search by city" << endl;
  }
  if (!options_arr[1].used) {
    cout << "              " << options_arr[1].selection << ". Search by price range" << endl;
  }
  if (!options_arr[2].used) {
    cout << "              " << options_arr[2].selection << ". Search by origin" << endl;
  }
  if (!options_arr[3].used) {
    cout << "              " << options_arr[3].selection << ". Search by fanciness" << endl;
  }
  if (!options_arr[4].used) {
    cout << "              " << options_arr[4].selection << ". Pick a random restuarant for me!" << endl;
  }
  cout << "\nPlease input your selection by the number -> ";


  int selection;
  int bad_input;
  do{
    bad_input = 0;
    cin >> selection;
    if(!cin)
    {
      bad_input=1;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    }
  }while(bad_input);
  for (Option op : options_arr) {
    if (op.selection == selection) {
      op.used = true;
      return op.order;
    }
  }

  return 'e';
}

// Prompt user for city filtering and use mapping to return City enum
City city_search() {
  cout << "\nWhich city would you like to search through? -> ";
  cin.ignore();
  string query;
  getline (cin, query);
  transform(query.begin(), query.end(), query.begin(),(int (*)(int))toupper);
  return city_map.find(query)->second;
}

// Prompt user for price filtering and return int of price
int price_search() {
  cout << "\nWhich price would you like to search through? (enter number between 1 and 4) -> ";
  cin.ignore();
  int price_range;
  cin >> price_range;
  return price_range;
}

// Prompt user for origin filtering and use mapping to return Origin enum
Origin origin_search() {
  cout << "\nWhich type of food would you like to search through? -> ";
  cin.ignore();
  string query;
  getline (cin, query);
  transform(query.begin(), query.end(), query.begin(),(int (*)(int))toupper);
  return origin_map.find(query)->second;
}

// Prompt user for level filtering and use mapping to return Level enum
Level level_search() {
  cout << "\nWhich fanciness of restaurants would you like to search through? -> ";
  cin.ignore();
  string query;
  getline (cin, query);
  transform(query.begin(), query.end(), query.begin(),(int (*)(int))toupper);
  return level_map.find(query)->second;
}

// Create vector of valid Restaurant objects given vector of all Restaurant objects
// return random Restaurant object from vector of valid restaurants
Restaurant pick_restaurant(vector<Restaurant>& prelist) {
  srand(time(NULL));
  vector<Restaurant> list;
  for (Restaurant r : prelist) {
    if (r.get_filter()) {
      list.push_back(r);
    }
  }
  if (list.size() == 0) {
    return Restaurant("No restaurants to pick from", no_where, 0, none, no_class);
  }
  int random_index = rand() % list.size();
  return list[random_index];
}

// Helper function for menu()
// updates options_arr so that filters are not reused and order is updated
void update_op_arr(vector<Option>& options_arr, char chosen_option) {
  bool change = false;
  for (Option& op : options_arr) {
    if (op.order == chosen_option) {
      op.used = true;
      change = true;
    }
    if (change) {
      --op.selection;
    }
  }
}

// Insert all restaurant data into vector of Restaurant objects
void insert_restaurants(vector<Restaurant>& restaurants) {
  restaurants.push_back( Restaurant("Gyu Kaku", cupertino, 3, japanese, moderate));
  restaurants.push_back( Restaurant("Panda Express", cupertino, 1, fast_food, casual));
  restaurants.push_back( Restaurant("In-N-Out", sunnyvale, 1, fast_food, casual));
  restaurants.push_back( Restaurant("Wendy's", san_jose, 1, fast_food, casual));
  restaurants.push_back( Restaurant("Five Guys", san_jose, 1, fast_food, casual));
  restaurants.push_back( Restaurant("Habit Burger", cupertino, 1, fast_food, casual));
  restaurants.push_back( Restaurant("The Counter", cupertino, 2, american, moderate));
  restaurants.push_back( Restaurant("Sushi Boat", san_jose, 3, japanese, moderate));
  restaurants.push_back( Restaurant("Don Giovanni", mountain_view, 3, italian, moderate));
  restaurants.push_back( Restaurant("Crepe Vine", mountain_view, 2, brunch, moderate));
  restaurants.push_back( Restaurant("Bill of Fare", san_jose, 2, brunch, moderate));
  restaurants.push_back( Restaurant("Bobby's Cafe", cupertino, 2, brunch, moderate));
  restaurants.push_back( Restaurant("OG Pancake House", cupertino, 2, brunch, moderate));
  restaurants.push_back( Restaurant("Chick-fil-a", sunnyvale, 1, fast_food, casual));
  restaurants.push_back( Restaurant("Orenchi", santa_clara, 2, japanese, moderate));
  restaurants.push_back( Restaurant("Misoya", san_jose, 2, japanese, casual));
  restaurants.push_back( Restaurant("Sentouka", san_jose, 2, japanese, casual));
  restaurants.push_back( Restaurant("Bull KBBQ", cupertino, 4, korean, mama_huang));
  restaurants.push_back( Restaurant("Gen KBBQ", san_jose, 4, korean, mama_huang));
  restaurants.push_back( Restaurant("Q Pot", san_jose, 4, korean, mama_huang));
  restaurants.push_back( Restaurant("Coconuts", palo_alto, 3, other, moderate));
  restaurants.push_back( Restaurant("Layang Layang", cupertino, 2, other_asian, moderate));
  restaurants.push_back( Restaurant("Siam Thai", cupertino, 2, thai, moderate));
  restaurants.push_back( Restaurant("Ike's Sandwich", cupertino, 2, american, casual));
  restaurants.push_back( Restaurant("Boudin", cupertino, 2, american, casual));
  restaurants.push_back( Restaurant("Subway", cupertino, 1, fast_food, casual));
  restaurants.push_back( Restaurant("Rio Adobe", cupertino, 2, mexican, moderate));
  restaurants.push_back( Restaurant("KFC", cupertino, 1, fast_food, casual));
  restaurants.push_back( Restaurant("Popeye's", cupertino, 2, fast_food, casual));
  restaurants.push_back( Restaurant("Lemonade", palo_alto, 3, other, moderate));
  restaurants.push_back( Restaurant("Lee's", cupertino, 1, other_asian, casual));
  restaurants.push_back( Restaurant("Go Fish Poke", cupertino, 2, other_asian, casual));
  restaurants.push_back( Restaurant("Eureka!", cupertino, 2, other, moderate));
  restaurants.push_back( Restaurant("House of Falafel", cupertino, 2, medeteranian, casual));
  restaurants.push_back( Restaurant("Nick The Greek", cupertino, 2, greek, casual));
  restaurants.push_back( Restaurant("Stein's", cupertino, 3, american, moderate));
  restaurants.push_back( Restaurant("Saratoga Bagels", saratoga, 1, american, casual));
  restaurants.push_back( Restaurant("Oren's Hummus", cupertino, 3, medeteranian, moderate));
  restaurants.push_back( Restaurant("IHOP", san_jose, 1, brunch, casual));
  restaurants.push_back( Restaurant("Legend's Pizza", cupertino, 2, italian, moderate));
  restaurants.push_back( Restaurant("Pizza My Heart", cupertino, 2, italian, casual));
  restaurants.push_back( Restaurant("Nordstrom Bistro", san_jose, 3, american, moderate));
  restaurants.push_back( Restaurant("Pizza Antica", san_jose, 3, italian, moderate));
  restaurants.push_back( Restaurant("Yard House", san_jose, 3, american, moderate));
  restaurants.push_back( Restaurant("Mizu", san_jose, 4, japanese, mama_huang));
  restaurants.push_back( Restaurant("The Blue Door", saratoga, 3, greek, moderate));
  restaurants.push_back( Restaurant("Aqui's", cupertino, 2, mexican, moderate));
  restaurants.push_back( Restaurant("Taco Bell", cupertino, 1, fast_food, casual));
  restaurants.push_back( Restaurant("New Mangolian BBQ", mountain_view, 2, other_asian, moderate));
  restaurants.push_back( Restaurant("El Camino Mangolian BBQ", san_jose, 2, other_asian, moderate));
  restaurants.push_back( Restaurant("Ryowa", mountain_view, 2, japanese, moderate));
}

int main() {
  vector<Restaurant> restaurants;
  insert_restaurants(restaurants);
  print_header();
  vector<Option> options_arr {{.order = 'a', .selection = 1, .used = false},
                              {.order = 'b', .selection = 2, .used = false},
                              {.order = 'c', .selection = 3, .used = false},
                              {.order = 'd', .selection = 4, .used = false},
                              {.order = 'e', .selection = 5, .used = false}};
  bool print_restaurants = true;

  
  char option;
  do {
    option = menu(options_arr);
    update_op_arr(options_arr, option);
    switch (option) {
      case 'a':
        City filter_city;
        filter_city = city_search();
        for( Restaurant& r : restaurants ) {
          if (r.get_city() != filter_city) {
            r.filter_out();
          }
        }
      break;
      case 'b':
        int price_range;
        price_range = price_search();
        for( Restaurant& r : restaurants ) {
          if (r.get_price() != price_range) {
            r.filter_out();
          }
        }
      break;
      case 'c':
        Origin filter_origin;
        filter_origin = origin_search();
        for( Restaurant& r : restaurants ) {
          if (r.get_origin() != filter_origin) {
            r.filter_out();
          }
        }
      break;
      case 'd':
        Level filter_level;
        filter_level = level_search();
        for( Restaurant& r : restaurants ) {
          if (r.get_level() != filter_level) {
            r.filter_out();
          }
        }
      break;
      case 'e':
        cout << endl << "You're randomly picked restaurant is: " <<
        pick_restaurant(restaurants).to_string() << endl << "        Enjoy!" <<  endl << endl;
        print_restaurants = false;
      break;
    }
    if (print_restaurants) {
      for (Restaurant r : restaurants) {
        if (r.get_filter()) {
          cout << r.to_string();
        }
      }
    }
  } while (option != 'e');
  
  return 0;
}# restaurant_picker
