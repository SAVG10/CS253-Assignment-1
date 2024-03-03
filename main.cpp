#include<iostream>
#include<vector>
#include<chrono>
#include<fstream>
#include<istream>
#include<ostream>
#include<string>
#include<stdlib.h>
#include<sstream>
#include<utility>
#include<stdexcept> 
#include<cmath>



using namespace std;

vector<vector<string>> data_base;
vector<vector<string>> data_base_dup;
vector<string> new_modify;


//Functions for file handling
//referenced from java2blog.com

void readfile(string fname){
    vector<string> row;
    string line, word;

    fstream file (fname,ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')) row.push_back(word);
            data_base.push_back(row);
        }
    }
    else std::cout<<"Unable to open the file\n";
    file.close();
}

void writefile(vector<vector<string>> par, string fname){  
    fstream fout(fname,ios::out);
    for(auto x:par){
        for(auto y:x){
            fout<<y;
            if(y!=x.back()) fout<<",";
        }
        fout<<"\n";
    }
    fout.close();
}

void writefileappend(vector<string> par, string fname){  
    fstream fout(fname,ios::out | ios::app);
    for(auto x:par){
        fout<<x;
        if(x!=par.back()) fout<<",";
    }
    fout<<"\n";
    fout.close();
}

void printdata(vector<vector<string>> par){
    int c=1;
    for(auto x:par){
        std::cout<<c<<". ";
        for(auto y:x){
            std::cout<<y;
            if(y!=x.back()) std::cout<<" | ";
        }
        c++;
        std::cout<<"\n";
    }
}
void print_notpass(vector<vector<string>> par){
    int c=1;
    for(auto x:par){
        std::cout<<c<<". ";
        std::cout<<x[0]<<" | "<<x[1]<<" | "<<x[3]<<'\n';
        c++;
    }
}

//Starting of objects

class Car {
    public:

    //Characteristics
        string model;
        string condition;
        string amount;
        string n_avail;  //0 if the car is not available and 1 if the car is available

    //Functions
        void add_car(string model);
        void update_car(string model);
        void delete_car(string model);
        void rent_req(string model, string id, int user_goodness_value,string type_user);
        void show_ddate(string model);
};

class User{
    private:
        string password;
    public:

    //characteristics
        string name;
        string id;
        vector<string> cars_rented;
        string fine_due;
        string user_type;
        // 0 is the type of customer, 1 is the type of employee, 2 is the type of manager
        int user_goodness_value=50; 
        // the user value is the measure of the goodness index of the user and decides the number of cars he can rent.


    //Functions
        void display_menu();
        void registration();
        string username();
        void login();
        void see_all_cars(string id);
        void logout();
        void rent_car(string model, string name,int user_goodness_value,string user_type);
        void return_car(string id, string model);
        void check_available(string id,string model);
        int calc_fine(string id, string user_type,float amount);
        void clear_fine_amount(string id, string user_type);
        void User_add(string id);
        void User_update(string id);
        void User_delete(string id);
        void see_rented_cars(string id); //cars rented by the user
};

class Cust : public User {
    public:

    string fine;
    void display_menu_cust(string id);
};

class Employee : public User {
    public:
    
    string fine;
    void display_menu_em(string id);
};

class Manager : public User {
    public:

    void display_menu_manager(string id);
    void show_all_users(string id);
    void show_all_cars(string id);
    void add_user(string id);
    void update_user(string id);
    void delete_user(string id);
    void add_car(string model);
    void update_car(string model);
    void delete_car(string model);
    void show_rented_user(string id, string user_id);
    void show_rented_car(string model);
    // void show_rented_cars_user(string id, string model);
};


//All classes display menus

void Cust::display_menu_cust(string id){
    std::cout<< "********************************************************************\n";
    std::cout<<"\n";
    std::cout<<"Welcome Customer\n";
    std::cout<<"Select 1 to view all the cars\n";
    std::cout<<"Select 2 to view the cars rented by you\n";
    std::cout<<"Select 3 to check if a car is available\n";
    std::cout<<"Select 4 to rent a car\n";
    std::cout<<"Select 5 to return your rented car\n";
    std::cout<<"Select 6 to logout\n";
    std::cout<< "********************************************************************\n";
    int count;
    cin >> count;
    string model;
    Cust c;
    Car t;
    switch(count){
        case 1:
            c.see_all_cars(id);
            c.display_menu_cust(id);
            break;
        case 2:
            c.see_rented_cars(id);
            c.display_menu_cust(id);
            break;
        case 3:
            std::cout << "Enter the model of the car please\n";
            cin.ignore();
            getline(cin,model);
            c.check_available(id,model);
            c.display_menu_cust(id);
            break;
        case 4:
            std::cout << "Enter the model of the car please\n";
            cin.ignore();
            getline(cin,model);
            c.rent_car(model,id,c.user_goodness_value,"0");
            c.display_menu_cust(id);
            break;
        case 5:
            std::cout << "Enter the model of the car please\n";
            cin.ignore();
            getline(cin,model);
            c.return_car(id, model);
            c.display_menu_cust(id);
            break;
        case 6:
            c.logout();
            break;
    }
}

void Employee::display_menu_em(string id){
    std::cout<< "********************************************************************\n";
    std::cout<<"\n";
    std::cout<<"Welcome Employee\n";
    std::cout<<"Select 1 to view all the cars\n";
    std::cout<<"Select 2 to view the cars rented by you\n";
    std::cout<<"Select 3 to check if a car is available\n";
    std::cout<<"Select 4 to rent a car\n";
    std::cout<<"Select 5 to return your rented car\n";
    std::cout<<"Select 6 to logout\n";
    std::cout<< "********************************************************************\n";
    int count;
    cin >> count;
    string model;
    Employee c;
    Car t;
    switch(count){
        case 1:
            c.see_all_cars(id);
            c.display_menu_em(id);
            break;
        case 2:
            c.see_rented_cars(id);
            c.display_menu_em(id);
            break;
        case 3:
            std::cout << "Enter the model of the car please\n";
            cin.ignore();
            getline(cin,model);
            c.check_available(id,model);
            c.display_menu_em(id);
            break;
        case 4:
            std::cout << "Enter the model of the car please\n";
            cin.ignore();
            getline(cin,model);
            c.rent_car(model,id,c.user_goodness_value,"1");
            c.display_menu_em(id);
            break;
        case 5:
            std::cout << "Enter the model of the car please\n";
            cin.ignore();
            getline(cin,model);
            c.return_car(id, model);
            c.display_menu_em(id);
            break;
        case 6:
            c.logout();
            break;
    }
}

void Manager :: display_menu_manager(string id){
    std::cout<< "********************************************************************\n";
    std::cout<<"\n";
    std::cout<<"Welcome Manager\n";
    std::cout<<"Choose 1 to add a user\n";
    std::cout<<"Choose 2 to update a user\n";
    std::cout<<"Choose 3 to delete a user\n";
    std::cout<<"Choose 4 to add a car\n";
    std::cout<<"Choose 5 to update a car\n";
    std::cout<<"Choose 6 to delete a car\n";
    std::cout<<"Choose 7 to see the status of the car\n";
    std::cout<<"Choose 8 to show due date of a car\n";
    std::cout<<"Choose 9 to see all cars rented to a particular user\n";
    std::cout<<"Choose u to view all users\n";
    std::cout<<"Choose c to view all cars\n";
    std::cout<<"Choose l to logout\n";
    std::cout<< "********************************************************************\n";
    char c;
    cin>>c;
    Manager m;
    Car b;
    User u;
    string user_id;
    string model;
    switch(c){
        case '1':
            u.User_add(id);
            m.display_menu_manager(id);
            break;
        case '2':
            u.User_update(id);
            m.display_menu_manager(id);
            break;
        case '3':
            u.User_delete(id);
            m.display_menu_manager(id);
            break;
        case '4':
            b.add_car(id);
            m.display_menu_manager(id);
            break;
        case '5':
            b.update_car(id);
            m.display_menu_manager(id);
            break;
        case '6':
            b.delete_car(id);
            m.display_menu_manager(id);
            break;
       
        case '7':
            std::cout<<"Enter the model of the car : ";
            cin.ignore();
            getline(cin,model);
            m.show_rented_car(model);
            m.display_menu_manager(id);
            break;
        case '8':
            std::cout<<"Enter the model of the car : ";
            cin>>model;
            b.show_ddate(model);
            m.display_menu_manager(id);
            break;
        case '9':
            std::cout<<"Enter the id of the user : ";
            cin>>user_id;
            m.show_rented_user(id,user_id);
            m.display_menu_manager(id);
            break;
        case 'u':
            m.show_all_users(id);
            m.display_menu_manager(id);
            break;
        case 'c':
            m.show_all_cars(id);
            m.display_menu_manager(id);
            break;
        case 'l':
            logout();
            m.display_menu_manager(id);
            break;
    }
}

void User :: display_menu(){
    std::cout << "░██╗░░░░░░░██╗███████╗██╗░░░░░░█████╗░░█████╗░███╗░░░███╗███████╗  ████████╗░█████╗░\n";
    std::cout << "░██║░░██╗░░██║██╔════╝██║░░░░░██╔══██╗██╔══██╗████╗░████║██╔════╝  ╚══██╔══╝██╔══██╗\n";
    std::cout << "░╚██╗████╗██╔╝█████╗░░██║░░░░░██║░░╚═╝██║░░██║██╔████╔██║█████╗░░  ░░░██║░░░██║░░██║\n";
    std::cout << "░░████╔═████║░██╔══╝░░██║░░░░░██║░░██╗██║░░██║██║╚██╔╝██║██╔══╝░░  ░░░██║░░░██║░░██║\n";
    std::cout << "░░╚██╔╝░╚██╔╝░███████╗███████╗╚█████╔╝╚█████╔╝██║░╚═╝░██║███████╗  ░░░██║░░░╚█████╔╝\n";
    std::cout << "░░░╚═╝░░░╚═╝░░╚══════╝╚══════╝░╚════╝░░╚════╝░╚═╝░░░░░╚═╝╚══════╝  ░░░╚═╝░░░░╚════╝░\n";
    std::cout << "\n\n";
    std::cout << "░█████╗░░█████╗░██████╗░  ░█████╗░  ███╗░░░███╗░█████╗░████████╗██████╗░██╗██╗░░██╗\n";
    std::cout << "██╔══██╗██╔══██╗██╔══██╗  ██╔══██╗  ████╗░████║██╔══██╗╚══██╔══╝██╔══██╗██║╚██╗██╔╝\n";
    std::cout << "██║░░╚═╝███████║██████╔╝  ███████║  ██╔████╔██║███████║░░░██║░░░██████╔╝██║░╚███╔╝░\n";
    std::cout << "██║░░██╗██╔══██║██╔══██╗  ██╔══██║  ██║╚██╔╝██║██╔══██║░░░██║░░░██╔══██╗██║░██╔██╗░\n";
    std::cout << "╚█████╔╝██║░░██║██║░░██║  ██║░░██║  ██║░╚═╝░██║██║░░██║░░░██║░░░██║░░██║██║██╔╝╚██╗\n";
    std::cout << "░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝  ╚═╝░░╚═╝  ╚═╝░░░░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝\n";
    char c;
    std::cout<< "********************************************************************\n";
    std::cout<<"1. Choose 1 to enter the Car Matrix\n";
    std::cout<<"2. Choose 2 to register\n";
    std::cout<<"3. Choose 3 to exit\n";
    std::cout<< "********************************************************************\n";
    cin>>c;
    if(c=='1'){ // User enter
        User u;
        u.login();
    }
    if(c=='2'){
        User u;
        u.registration();
    }
    else{
        std::cout<<"Good Bye, hope you enjoyed the matrix !\n";
        exit(1);
    }
}

string User::username(){
    int counter=0;
    string user_id;
    User u;
    std::cout<<"Please enter the user id : ";
    cin>> user_id;
    readfile("all_users_data.csv");
    for(int i=0;i<data_base.size();i++){
        if (data_base[i][1]==user_id){
            counter++;
        }
    }
    if(counter==0){
        std::cout << "User ID is available and is successfully assigned !\n";
    }
    else{
        std::cout<<"User ID is already taken.";
        user_id=u.username();
    }
    return user_id;
}




void User::registration(){
    User u;
    string c;
    string name,user_id,password,user_type;
    int counter=0;
    data_base.clear();
    std::cout<<"Thank you for choosing Car-A-Matrix\n";
    std::cout<<"Enter the Matrix as a :- \n";
    std::cout<<"0. Choose 0 as a customer\n";
    std::cout<<"1. Choose 1 as an employee.\n";
    std::cout<<"2. Choose 2 as a manager.\n";
    cin>>c;
    if(c=="0"){
        user_type="0";
        std::cout<<"Welcome Customer !\n";
        std::cout<<"Please enter your name :";
    }
    else if(c=="1"){
        user_type="1";
        std::cout<<"Welcome Employee !\n";
        std::cout<<"Please enter your name :";
    }
    else if(c=="2"){
        user_type="2";
        std::cout<<"Welcome Manager !\n";
        std::cout<<"Please enter your name :";
    }
    else{
        std::cout<<"Don't mess with the Matrix. It may devour you !!\n";
        std::cout<<"Please enter valid details.\n";
        u.registration();
    }
    cin.ignore();
    getline(cin,name);
    user_id=u.username();
    std::cout<<"Please enter your password : ";
    cin.ignore();
    getline(cin,password);
    new_modify.clear();
    new_modify.push_back(name);
    new_modify.push_back(user_id);
    new_modify.push_back(password);
    new_modify.push_back(user_type);
    new_modify.push_back("50");
    writefileappend(new_modify,"all_users_data.csv");
    if(c=="0"){
        std::cout<<"You have been successfully registered as a customer !\n";
        writefileappend(new_modify,"all_customers_data.csv");
    }
    else if(c=="1"){
        std::cout<<"You have been successfully registered as an employee !\n";
        writefileappend(new_modify,"all_employees_data.csv");
    }
    else if(c=="2"){
        std::cout<<"You have been successfully registered as a Manager !\n";
        writefileappend(new_modify,"all_managers_data.csv");
    }
    u.display_menu();
}
    
void User :: login(){
    string id;
    string password;
    std::cout<<"Enter your id : ";
    cin>>id;
    std::cout<<"Enter the password : ";
    cin>>password;
    vector<string> word_row;
    string line_csv,word;
    fstream file("all_users_data.csv",ios::in);
    int count=0;
    if(file.is_open()){
        while(getline(file,line_csv)){
            word_row.clear();
            stringstream str(line_csv);
            while(getline(str,word,',')) word_row.push_back(word);
            if(word_row[1]==id){
                count=1;
                if(word_row[2]==password){
                    count++;
                    break;
                }
                else{
                    while(password!=word_row[2]){
                        std::cout<<"You entered the wrong password. Choose 1 to reenter the password and 2 to exit\n";
                        char c;
                        cin>>c;
                        if(c=='1'){
                            std::cout<<"Enter the password : ";
                            cin>>password;
                            if(password==word_row[2]) count++;
                        }
                        else if(c=='2'){
                            std::cout<<"Leaving the Matrix...";
                            return;
                        }
                        else{
                            std::cout<<"Please enter a valid input.\n";
                        }
                    }
                    if(count==2) break;
                }
            }
            if(count==2) break;            
        }
        if(count==0){
            std::cout<<"User not found\n";
            User u;
            u.display_menu();
        }
        if(count==2){

            Cust c;
            Employee e;
            Manager m;

            if(word_row[3]=="0"){
                c.display_menu_cust(word_row[1]);
            }
            else if(word_row[3]=="1"){
                e.display_menu_em(word_row[1]);
            }
            else{
                m.display_menu_manager(word_row[1]);
            }
        }
    }
}

void User :: see_all_cars(string id){
    data_base.clear();
    std::cout<<"Below, 0 says that the car can be rented and 1 says the cars has already been rented.\n";
    readfile("all_cars_data.csv");
    printdata(data_base);
    data_base.clear();
}

//Finish the seg fault
void User :: rent_car(string model, string id,int user_goodness_value, string type_user){
    data_base.clear();
    int counter=0;
    int count=0;
    string amount;
    data_base.clear();
    readfile("rented_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][0]==id){
            count++;
        }
    }
    data_base.clear();
    if(count>=user_goodness_value/10){
        std::cout<<"You cannot rent more than" <<user_goodness_value/10<<" cars !\n\n";
    }
    else{
        readfile("all_cars_data.csv");
        for(int i=0;i<data_base.size();i++){
            if(data_base[i][0]==model && data_base[i][3]=="0"&& stoi(data_base[i][1])>30){
                counter=1;
                amount=data_base[i][2];
                std::cout<<"Car is available to rent !\n";
                data_base[i][3]="1";
                new_modify.clear();
                new_modify.push_back(id);
                new_modify.push_back(model);
                new_modify.push_back(data_base[i][2]);
                new_modify.push_back(data_base[i][3]);
                new_modify.push_back(to_string(time(0)));
                writefileappend(new_modify,"rented_cars_data.csv");
                break;
            }
        }
        writefile(data_base,"all_cars_data.csv");
        data_base.clear();
        readfile("all_users_data.csv");
        string user_type;
        for(int i=0;i<data_base.size();i++){
            if(data_base[i][1]==id){
                user_type=data_base[i][3];
            }
        }
        if(counter==1){
            if(user_type=="0"){
                std::cout<<"Car succesfully rented !\n";
                std::cout<<"The rental period of the car is 5 days\n";
                std::cout<<"Please pay a rental fee of "<<ceil(stof(amount))<<"Rs. to the manager.\n";
            }
            if(user_type=="1"){
                std::cout<<"Car succesfully rented with a 15 percent discount !\n";
                std::cout<<"The rental period of the car is 7 days\n";
                std::cout<<"Please pay a rental fee of "<<ceil(stof(amount)*0.85)<<"Rs. to the manager.\n ";
            }
        }
        if(counter==0) std::cout<<"Car not available !\n";
        data_base.clear();

    }
}

void User :: return_car(string id, string model){
    data_base.clear();
    int counter=0;
    float amount;
    string user_type;
    readfile("all_users_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==id){
            user_type=data_base[i][3];
        }
    }
    data_base.clear();
    readfile("rented_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==model && data_base[i][0]==id){
            counter=1;
            data_base.erase(data_base.begin()+i,data_base.begin()+i+1);
            std::cout<<"This car was rented and is now being returned.\n";
            writefile(data_base,"rented_cars_data.csv");
            data_base.clear();
            readfile("all_cars_data.csv");
            for(int i=0;i<data_base.size();i++){
                if(data_base[i][0]==model){
                    data_base[i][3]="0";
                    data_base[i][1]=to_string(stoi(data_base[i][1])-10);
                    amount=stof(data_base[i][2]);
                } 
            }
            writefile(data_base,"all_cars_data.csv");
            break;
        }
    }
    if(counter==0) std::cout<<"Invalid details!\n";
    data_base.clear();
    if(counter!=0){
        calc_fine(id,user_type,amount);
    }
}

void User :: see_rented_cars(string id){
    int count=0;
    data_base.clear();
    readfile("rented_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][0]==id){
            count++;
            std::cout<<count<<". ";
            for(int k=0;k<data_base[i].size()-1;k++)
                std::cout<<data_base[i][k]<<" | ";
            time_t time = stoi(data_base[i][4]);
            tm *dateformat = localtime(&time);  
            std::cout<< (dateformat->tm_mday)<<"/"<<1 + dateformat->tm_mon<<"/"<<1900 + dateformat->tm_year<<"\n";
        }
    }
    if(count==0) std::cout<<"You have no rented cars !\n\n";
    data_base.clear();
}

void User :: check_available(string id,string model){
    data_base.clear();
    int counter=0;
    readfile("all_cars_data.csv");
    int count=1;
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][0]==model && data_base[i][3]=="0"){
            counter=1;
            std::cout<<count<<". ";
            count++;
            if(stoi(data_base[i][1])>30){
                std::cout<<"Car can be rented !\n";
                for(auto j:data_base[i])
                    std::cout<<j<<" | ";
                std::cout<<"\n";
                break;
            }
            else{
                std::cout<<"The Car connot be rented due to its poor condition.\n";
            }
        }
    }
    if(counter==0) std::cout<<"Car cannot be rented or is not available.\n";
    data_base.clear();
}

int User :: calc_fine(string id, string user_type, float amount){
    int fine=0;
    int user_goodness_value_decrement=0;
    int curtime;
    int isstime;
    if(user_type=="0"){
        data_base.clear();
        readfile("rented_cars_data.csv");
        // cout << "doing0" << endl;
        // cout << data_base.size() << " " << endl;
        for(int i=0;i<data_base.size();i++){
            // cout << i << " " << endl;
            if(data_base[i][0]==id){
                curtime = time(0);
                isstime = stoi(data_base[i][4]);
                user_goodness_value_decrement=((curtime-isstime)/86400-5);
                if(((curtime-isstime)/86400)>5) {
                    fine+=((curtime-isstime)/86400 - 5)*(amount)/4;
                }
                // cout << curtime << " " << isstime << " " << fine << " " << endl;
            }
        }
    }
    if(user_type=="1"){
        data_base.clear();
        readfile("rented_cars_data.csv");
        // cout << "doing1" << endl
        for(int i=0;i<data_base.size();i++){
            if(data_base[i][0]==id){
                int curtime = time(0);
                int isstime = stoi(data_base[i][4]);
                user_goodness_value_decrement=((curtime-isstime)/86400-7);
                if((curtime-isstime)/86400>7) {
                    fine+=2*((curtime-isstime)/86400 - 7)*(amount)/4;
                }
            }
        }
    }
    data_base.clear();
    readfile("all_users_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==id){
            data_base[i][4]=to_string(stoi(data_base[i][4])-user_goodness_value_decrement);
            if(stoi(data_base[i][4])>100){
                data_base[i][4]="100";
            }
            if(stoi(data_base[i][4])<10){
                data_base[i][4]="10";
            }
        }
    }
    if(user_goodness_value_decrement==0){
        std::cout<<"The way the matrix thinks of you doesn't change !\n";
    }
    else if(user_goodness_value_decrement<0){
        std::cout<<"The matrix thinks more positively of you !\n";
    }
    else{
        std::cout<<"Your status in the eyes of Matrix falls further !\n";
    }
    writefile(data_base,"all_users_data.csv");
    data_base.clear();
    readfile("all_users_data.csv");
    data_base_dup.clear();
    for(int i=0;i<data_base.size();i++){
        if(user_type==data_base[i][3]){
            data_base_dup.push_back(data_base[i]);
        }
    }
    if(user_type=="0"){
        writefile(data_base_dup,"all_customers_data.csv");
    }
    if(user_type=="1"){
        writefile(data_base_dup,"all_employees_data.csv");
    }
    if(user_type=="2"){
        writefile(data_base_dup,"all_managers_data.csv");
    }
    std::cout<<"Your fine is : "<<fine<<"\n";
    data_base.clear();
    return fine;
}

void User :: logout(){
    std::cout<<"Leaving the Matrix...\n";
    User u;
    u.display_menu();
}

//Manager Functions

void User :: User_add(string id){
    Manager m;
    m.add_user(id);
}

void User :: User_delete(string id){
    Manager m;
    m.delete_user(id);
}

void User :: User_update(string id){
    Manager m;
    m.update_user(id);
}


//A normal customer can rent for 5 days whereas an employee can rent for 7 days
void Car :: show_ddate(string model){
    data_base.clear();
    string user_id;
    time_t time;
    readfile("rented_cars_data.csv");
    int counter=0;
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==model){
            counter=1;
            user_id = data_base[i][0];
            time = stoi(data_base[i][4]);
            break;
        }
    }
    data_base.clear();
    int days=30;
    readfile("all_users_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==user_id){
            if(data_base[i][3]=="0")
                days=5;
            else
                days=7;
            break;
        }
    }
    time+=days*86400;
    tm *due_time = localtime(&time);  
    if(counter==0) std::cout<<"Car was not rented!\n";
    else{
        std::cout<<"Due date of the car is : ";
        std::cout<< due_time->tm_mday<<"/"<<1 + due_time->tm_mon<<"/"<<1900 + due_time->tm_year<<"\n";
    }
}

void Car :: rent_req(string model, string id, int user_goodness_value,string type_user ){
    User u;
    u.rent_car(model, id, user_goodness_value,type_user);
}
void Car :: add_car(string id){
    Manager m;
    m.add_car(id);
}
void Car :: delete_car(string id){
    Manager m;
    m.delete_car(id);
}
void Car :: update_car(string id){
    Manager m;
    m.update_car(id);
}

void Manager :: show_all_users(string id){
    data_base.clear();
    readfile("all_users_data.csv");
    std::cout<<"The following is the list of all the users.\n\n";
    std::cout<<"The data is given in the form of name, id and the type of the user.\n\n";
    std::cout<<"0 at the end represents a normal customer, 1 represent an employee and 2 represents a manager.\n";
    print_notpass(data_base);
    data_base.clear();
}
void Manager :: show_all_cars(string id){
    data_base.clear();
    readfile("all_cars_data.csv");
    std::cout<<"The following is the list of all the cars\n\n";
    std::cout<<"The data is given in the format of model, condition, amount and availability of the car where 1 means already rented.\n\n";
    std::cout<<"The condition ranges from 0 to 100 and you cannot rent a car with condition below 35.\n\n";
    printdata(data_base);
    data_base.clear();
}
void Manager :: add_user(string id){
    std::cout<<"Enter the details of the new user : \n";
    string name,user_id,password,user_type;
    int user_goodness_value;
    std::cout<<"Enter the name: ";
    cin.ignore();
    getline(cin,name);
    user_id=username();
    std::cout<<"Enter the password : ";
    cin>>password;
    std::cout<<"Enter the type of the user : 0 for customer, 1 for employee, 2 for manager : ";
    cin>>user_type;
    user_goodness_value=50;
    fstream fout("all_users_data.csv",ios::out | ios::app);
    fout<<name<<","<<user_id<<","<<password<<","<<user_type<<","<<user_goodness_value<<'\n';
    if(user_type=="0"){
        fstream fout("all_customers_data.csv",ios::out | ios::app);
        fout<<name<<","<<user_id<<","<<password<<","<<user_type<<","<<user_goodness_value<<'\n';
    }
    else if(user_type=="1"){
        fstream fout("all_employees_data.csv",ios::out | ios::app);
        fout<<name<<","<<user_id<<","<<password<<","<<user_type<<","<<user_goodness_value<<'\n';
    }
    else if(user_type=="2"){
        fstream fout("all_managers_data.csv",ios::out | ios::app);
        fout<<name<<","<<user_id<<","<<password<<","<<user_type<<","<<user_goodness_value<<'\n';
    }
    std::cout<<"New user has been registered.\n";
}
void Manager :: add_car(string id){
    std::cout<<"Please enter the details of the new car : \n";
    string model,condition,amount;
    std::cout<<"Enter the model of the car: ";
    cin.ignore();
    getline(cin,model);
    std::cout<<"Enter the condition of the car : ";
    cin>>condition;
    std::cout<<"Enter the rental price of the car : ";
    cin>>amount;
    fstream fout("all_cars_data.csv",ios::out | ios::app);
    fout<<model<<","<<condition<<","<<amount<<",0"<<'\n';
    std::cout<<"New car has been added to our database.\n";
}
void Manager :: delete_car(string id){
    string model;
    std::cout<<"Enter the model of the car : ";
    cin>>model;
    data_base.clear();
    int found=0;
    readfile("all_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][0]==model){
            found=1;
            data_base.erase(data_base.begin()+i,data_base.begin()+i+1);
            break;
        }
    }
    writefile(data_base,"all_cars_data.csv");
    data_base.clear();
    readfile("rented_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==model){
            data_base.erase(data_base.begin()+i,data_base.begin()+i+1);
            break;
        }
    }
    writefile(data_base,"rented_cars_data.csv");
    data_base.clear();
    if(found==0) std::cout<<"Car not found in the database.\n";
    else{
        std::cout<<"The Car has been removed from the database.\n";
    }
}
void Manager :: delete_user(string id){
    string user_id;
    string user_type;
    std::cout<<"Enter the user id of the user : ";
    cin>>user_id;
    data_base.clear();
    int found=0;
    readfile("all_users_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==user_id){
            found=1;
            user_type=data_base[i][3];
            data_base.erase(data_base.begin()+i,data_base.begin()+i+1);
            break;
        }
    }
    writefile(data_base,"all_users_data.csv");
    data_base.clear();
    vector<string> model;
    readfile("rented_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][0]==user_id){
            model.push_back(data_base[i][1]);
            data_base.erase(data_base.begin()+i);
            break;
        }
    }
    writefile(data_base,"rented_cars_data.csv");
    data_base.clear();

    readfile("all_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        for(int j=0;j<model.size();j++){
            if(model[j]==data_base[i][0]){
                data_base[i][3]="0";
            }
        }
    }
    writefile(data_base,"all_cars_data.csv");
    data_base.clear();
    readfile("all_users_data.csv");
    data_base_dup.clear();
    for(int i=0;i<data_base.size();i++){
        if(user_type==data_base[i][3]){
            data_base_dup.push_back(data_base[i]);
        }
    }
    if(user_type=="0"){
        writefile(data_base_dup,"all_customers_data.csv");
    }
    if(user_type=="1"){
        writefile(data_base_dup,"all_employees_data.csv");
    }
    if(user_type=="2"){
        writefile(data_base_dup,"all_managers_data.csv");
    }
    if(found==0) std::cout<<"User not found.\n";
    else{
        std::cout<<"User has been removed from the Matrix.\n";
    }
}
void Manager :: update_user(string id){
    int counter=0;
    string user_id;
    string user_type;
    std::cout<<"Enter the id of the user you want to update : ";
    cin>>user_id;
    readfile("all_users_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==user_id){
            counter++;
        }  
    }
    if(counter==0){
        std::cout<<"User was not found in the Matrix.\n\n";
    }
    else{
        std::cout<<"Choose the field you want to update : \n";
        std::cout<<"1. Name of the User\n";
        std::cout<<"2. Type of the User\n";
        std::cout<<"3. Goodness index of the User\n";
        char c;
        cin>>c;
        data_base.clear();
        readfile("all_users_data.csv");
        for(int i=0;i<data_base.size();i++){
            if(data_base[i][1]==user_id){
                string updated_value;
                user_type=data_base[i][3];
                if(c=='1'){
                    std::cout<<"Enter the updated value of "<<"the Name of the user" << " so that the Matrix is updated to be omniscient.\n";
                    cin.ignore();
                    getline(cin,updated_value);
                    data_base[i][0]=updated_value;
                    std::cout<<"User data updated\n";
                }
                else if(c=='2'){
                    std::cout<<"Enter the updated value of "<<"the Type of the user" <<" so that the Matrix is updated to be omniscient.\n";
                    cin.ignore();
                    getline(cin,updated_value);
                    data_base[i][3]=updated_value;
                    std::cout<<"User data updated\n";
                }
                else if(c=='3'){
                    std::cout<<"Enter the updated value of "<<"the Goodness index of the user" <<" so that the Matrix is updated to be omniscient.\n";
                    cin.ignore();
                    getline(cin,updated_value);
                    data_base[i][4]=updated_value;
                    std::cout<<"User data updated\n";
                }
                else{
                    std::cout<<"Invalid input!\n\n";
                }
                break;
            }
        }
    writefile(data_base,"all_users_data.csv");
    data_base.clear();
    readfile("all_users_data.csv");
    data_base_dup.clear();
    for(int i=0;i<data_base.size();i++){
        if(user_type==data_base[i][3]){
            data_base_dup.push_back(data_base[i]);
        }
    }
    if(user_type=="0"){
        writefile(data_base_dup,"all_customers_data.csv");
    }
    if(user_type=="1"){
        writefile(data_base_dup,"all_employees_data.csv");
    }
    if(user_type=="2"){
        writefile(data_base_dup,"all_managers_data.csv");
    }
    data_base.clear();
    }
}
void Manager :: update_car(string id){
    int counter=0;
    string model;
    std::cout<<"Enter the model of the car you want to update : ";
    cin>>model;
    data_base.clear();
    string updated_value;
    readfile("all_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][0]==model){
            counter++;
        }  
    }
    if(counter==0){
        std::cout<<"Car was not found in the database.\n";
    }
    else{
        std::cout<<"Choose the field you want to update : \n";
        std::cout<<"1. Condition of the car\n";
        std::cout<<"2. Rental Price of the car\n";
        char c;
        cin>>c;
        for(int i=0;i<data_base.size();i++){
            if(data_base[i][0]==model){
                if(c=='1'){
                    std::cout<<"Enter the updated value of "<<"the condition of the car" << " so that the Matrix is updated to be omniscient.\n";
                    cin.ignore();
                    getline(cin,updated_value);
                    data_base[i][1]=updated_value;
                    std::cout<<"Car updated\n";
                }
                else if(c=='2'){
                    std::cout<<"Enter the updated value of "<<"the rental fee of the car" << " so that the Matrix is updated to be omniscient.\n";
                    cin.ignore();
                    getline(cin,updated_value);
                    data_base[i][2]=updated_value;
                    std::cout<<"Car updated\n";
                }
                else{
                    std::cout<<"Invalid input!\n\n";
                }
                break;
            }
        }
        writefile(data_base,"all_cars_data.csv");
        data_base.clear();
        
        readfile("rented_cars_data.csv");
        for(int i=0;i<data_base.size();i++){
            if(data_base[i][2]==model){
                counter=1;
                if(c=='1'){
                    data_base[i][1]=updated_value;
                }
                break;
            }
        }
        writefile(data_base,"rented_cars_data.csv");
    }

}

//Will show which cars a particular user has rented
void Manager :: show_rented_user(string id,string user_id){
    vector <string> model;
    data_base.clear();
    int count=1;
    readfile("rented_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][0]==user_id){
            model.push_back(data_base[i][1]);
        }
    }
    data_base.clear();
    if(model.size()==0) std::cout<<"No car was rented by this user.\n\n";
    else{
        readfile("all_cars_data.csv");
        for(int d=0;d<model.size();d++){
            for(int i=0;i<data_base.size();i++){
                if(data_base[i][0]==model[d]){
                    std::cout<<count<<". ";
                    count++;
                    for(auto y:data_base[i]){
                        if(y!=data_base[i].back())
                            std::cout<<y<<" | ";
                        else
                            std::cout<<y<<"\n";
                    }
                }
            }
        }
        data_base.clear();
    }
}

//Will show the user who has rented a particular car
void Manager :: show_rented_car(string model){
    data_base.clear();
    int counter=0;
    readfile("rented_cars_data.csv");
    for(int i=0;i<data_base.size();i++){
        if(data_base[i][1]==model){
            std::cout<<"The Car of model "<<model<<" was rented by user with id : "<<data_base[i][0]<<"\n";
            counter++;
        }
    }
    if(counter==0) std::cout<<"Car was not rented by anyone.\n\n";
}


//Displays the menu for navigation
int main(){
    User temp;
    temp.display_menu();
    return 0;
} 