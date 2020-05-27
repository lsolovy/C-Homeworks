/*Name: Louie Solovy
Date: 2/12/2020
Name of program: Dog class program
Description of program: This program uses one class named Dog that given an input of months
 will can calculate functions that are within the class based on what the user wants to have printed out.
 At the end of the program it will unit test the Dog class to test for possibilities of what the input of months
 could be.
input: months (based on the input of months you can calculate whichever outputs you would like (that are defined in the Dog class))
outputs:addBirthday,getMonths,getStage,HumanYears,DogYears ( These are all the outputs that can be tested for using the input months)
 */
#include <iostream>
using namespace std;
//class definition
class Dog {
public:
    //functions definitions in the class
    void setMonths(int monthsToSet);
    void addBirthday();
    string getStage() const;
    int getMonths () const;
    double HumanYears() const;
    double DogYears() const;
    explicit Dog(int Initialmonths = 1);
private:
    int months;
};
// default contrsutor
Dog::Dog(int Initialmonths){
    setMonths(Initialmonths);

}

int Dog :: getMonths() const {
    return months;

}
// will make sure month is 1 even if the input is less than 1
void Dog :: setMonths(int monthsToSet) {
    if(monthsToSet < 1){
        months = 1;
    }
    else{
        months = monthsToSet;
    }

}
//calculates human years from input months
double Dog :: HumanYears() const {
    return (months/12.0);
}
//calculates dog years from input months
double Dog :: DogYears() const {
    return ((months/12.0)*7.0);

}
//adds 12 to months
void Dog :: addBirthday() {
    months += 12;
}

//based on months will tell what stage the object is in
string Dog:: getStage() const {
    string stage;
    if(months < 11){
        stage = "Puppy";
    }
    else if(months < 25){
        stage = "Adolescence";
    }
    else if(months < 80){
        stage = "Adulthood";
    }
    else{
        stage = "Senior";
    }
    return stage;
}

int main() {
    //Unit testing for 4 objects with 4 test
    Dog Louie;
    cout << "\nExpected Louie.getMonth to return 1. Actual value is: "<< Louie.getMonths()<< endl;
    cout << "Expected Louie.getStage to return Puppy. Actual value is: "<< Louie.getStage()<< endl;
    cout << "Expected Louie.HumanYears to return .083. Actual value is: "<< Louie.HumanYears()<< endl;
    cout << "Expected Louie.DogYears to return .583. Actual value is: " << Louie.DogYears()<< endl;
    Dog Lou(-5);
    Lou.addBirthday();
    cout << "\nExpected Lou.getMonth to return 1 + 12 = 13. Actual value is: "<< Lou.getMonths()<< endl;
    cout << "Expected Lou.getStage to return Puppy. Actual value is: "<< Lou.getStage()<< endl;
    cout << "Expected Lou.HumanYears to return .083. Actual value is: "<< Lou.HumanYears()<< endl;
    cout << "Expected Lou.DogYears to return .583. Actual value is: "<< Lou.DogYears()<< endl;
    Dog Louis(27);
    cout << "\nExpected Louis.getMonth to return 27. Actual value is: "<< Louis.getMonths()<< endl;
    cout << "Expected Louis.getStage to return Adulthood. Actual value is: "<< Louis.getStage()<< endl;
    cout << "Expected Louis.HumanYears to return 2.25 .Actual value is: "<< Louis.HumanYears()<< endl;
    cout << "Expected Louis.DogYears to return 15.75. Actual value is: "<< Louis.DogYears()<< endl;
    Dog Luis(90);
    Luis.addBirthday();
    cout << "\nExpected Luis.getMonth to return 90 + 12 = 102. Actual value is: "<< Luis.getMonths()<< endl;
    cout << "Expected Luis.getStage to return Senior. Actual value is: "<< Luis.getStage()<< endl;
    cout << "Expected Luis.HumanYears to return 7.5. Actual value is: "<< Luis.HumanYears()<< endl;
    cout << "Expected Luis.DogYears to return 52.5. Actual value is: "<< Luis.DogYears()<< endl;

    return 0;


}
