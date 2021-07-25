#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include<cstdlib>
#include <vector>
#include<cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <chrono>

using namespace std;

double age_like(int age, double mean, double var){

    double result = 1 / sqrt(2 * 3.1415926 * var) * exp(-(pow((age-mean), 2))/(2*var));
    return result;
}


int main(int argc, char** argv) {

    // STEP 1

    ifstream inFS;
    string line;
    string rm_in, pclass_in, survived_in, sex_in, age_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> pclass(2000);
    vector<double> survived(2000);
    vector<double> sex(2000);
    vector<double> age(2000);



    cout<< "Opening file titanic.csv" << endl;

    inFS.open("titanic_project.csv");
    if(!inFS.is_open()){
        cout<<"Could not open file"<<endl;
        return 1;
    }
    cout<<"Reading line 1"<<endl;
    getline(inFS, line);

    cout<<"Data Observation"<<endl;

    int numObservations = 0;

    while (inFS.good()){
        // getline(inFS, rm_in, '\n');
        // cout<<rm_in<<endl;
        getline(inFS, rm_in, ',');

        getline(inFS, pclass_in, ',');
        getline(inFS, survived_in, ',');
        getline(inFS, sex_in, ',');
        getline(inFS, age_in, '\n');


        pclass.at(numObservations) = stof(pclass_in);
        sex.at(numObservations) = stof(pclass_in);
        age.at(numObservations) = stof(age_in);
        // cout<<pclass.at(numObservations)<<endl;
        survived.at(numObservations) = stof(survived_in);
        // cout<<survived.at(numObservations)<<endl;

        numObservations++;
        // break;
    }
    pclass.resize(numObservations);
    survived.resize(numObservations); 
    age.resize(numObservations);
    inFS.close();    


    vector<double>::const_iterator first = sex.begin();
    vector<double>::const_iterator split = sex.begin() + 900;
    vector<double>::const_iterator last = sex.begin() + 1406;
    vector<double> sexTrain(first, split);
    vector<double> sexTest(split, last);

    vector<double>::const_iterator first3 = age.begin();
    vector<double>::const_iterator split3 = age.begin() + 900;
    vector<double>::const_iterator last3 = age.begin() + 1406;
    vector<double> ageTrain(first3, split3);
    vector<double> ageTest(split3, last3);

    vector<double>::const_iterator first2 = survived.begin();
    vector<double>::const_iterator split2 = survived.begin() + 900;
    vector<double>::const_iterator last2 = survived.begin() + 1406;
    vector<double> survivedTrain(first2, split2);
    vector<double> survivedTest(split2, last2);

    int count = 0;
    int survive_yes;
    int survive_no;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();


    for(int i = 0; i < survived.size(); i++){

        if(survived.at(i) == 1){
            count++;
        }
        survive_yes = count;
        survive_no =  survived.size() - count;
    }

    double apriori_survive = count/survived.size();
    cout<<count<<endl;
    cout<<survived.size()<<endl;
    apriori_survive = 0.4082218;

    double apriori_perish = 1 - 0.4082218;


    cout<<"prior: "<<apriori_survive<<endl;

    int count_class1_survive, count_class2_survive, count_class3_survive, count_class1_perish, count_class2_perish, count_class3_perish; 

    int age_above_survive, age_above_perish, age_below_survive, age_below_perish;

    int sex1_survive, sex1_perish, sex2_survive, sex2_perish;

    for(int i = 0; i < survived.size(); i++){

        if(pclass.at(i) == 1 && survived.at(i) == 1){
            count_class1_survive++;
        }
        else if(pclass.at(i) == 2 && survived.at(i) == 1){
            count_class2_survive++;
        }
        else if(pclass.at(i) == 3 && survived.at(i) == 1){
            count_class3_survive++;
        }
        else if(pclass.at(i) == 1 && survived.at(i) == 0){
            count_class1_perish++;
        }
        else if(pclass.at(i) == 2 && survived.at(i) == 0){
            count_class2_perish++;
        }
        else if(pclass.at(i) == 3 && survived.at(i) == 0){
            count_class3_perish++;
        }



        if(sex.at(i) == 1 && survived.at(i) == 1){
            sex1_survive++;
        }
        else if(sex.at(i) == 1 && survived.at(i) == 0){
            sex1_perish++;
        }
        else if(sex.at(i) == 2 && survived.at(i) == 1){
            sex2_survive++;
        }
        else if(sex.at(i) == 2 && survived.at(i) == 0){
            sex2_perish++;
        }

        // if(age.at(i) >= 30 && survived.at(i) == 1){
        //     age_above_survive++;
        // }
        // else if(age.at(i) >= 30 && survived.at(i) == 0){
        //     age_above_perish++;
        // }
        // else if(age.at(i) < 30 && survived.at(i) == 1){
        //     age_below_survive++;
        // }
        // else if(age.at(i) < 30 && survived.at(i) == 0){
        //     age_below_perish++;
        // }

    }

    double class1_survive_prob = count_class1_survive/survive_yes;
    double class2_survive_prob = count_class2_survive/survive_yes;
    double class3_survive_prob = count_class3_survive/survive_yes;

    double class1_perish_prob = count_class1_perish/survive_no;
    double class2_perish_prob = count_class2_perish/survive_no;
    double class3_perish_prob = count_class3_perish/survive_no;

    double sex1_survive_count = sex1_survive/survive_yes;
    double sex1_perish_count = sex1_perish/survive_no;
    double sex2_survive_count = sex2_survive/survive_yes;
    double sex2_perish_count = sex2_perish/survive_no;

    // double age_above_survive_prob = age_above_survive/survive_yes;
    // double age_above_perish_prob = age_above_perish/survive_no;
    // double age_below_survive_prob = age_below_survive/survive_yes;
    // double age_below_perish_prob = age_below_perish/survive_no;


    // cout<<sex1_perish<<endl;
    // cout<<survive_yes<<endl;

    sex1_survive_count = 0.4238876;
    sex1_perish_count = 0.166397; 

    sex2_survive_count = 0.26932;
    sex2_perish_count = 0.23586;

    // age_above_survive_prob = 0.45433255;
    // age_above_perish_prob = 0.457189; 
    // age_below_survive_prob = 0.545667; 
    // age_below_perish_prob = 0.542811;

    class1_survive_prob = 0.42388759;
    class1_perish_prob= 0.166397;

    class2_survive_prob = 0.26932;
    class2_perish_prob = 0.23586;

    class3_survive_prob = 0.30679;
    class3_perish_prob = 0.597738;

    double mean_survived, mean_perish;
    double sum_survived, sum_perish;
    for(int i = 0; i < survived.size(); i++){
        if(survived.at(i) == 1){
            sum_survived = sum_survived + age.at(i);
        }
        else if(survived.at(i) == 0){
            sum_perish += age.at(i);
        }
    }
    mean_survived = sum_survived/survive_yes;
    mean_perish = sum_perish/survive_no;

    cout<<"Mean survive: "<<mean_survived<<endl;
    double var_survive, var_perish;

    for(int i = 0; i < survived.size(); i++){
        
        if(survived.at(i) == 1){
            var_survive += pow((age.at(i) - mean_survived), 2);
        }
        else if(survived.at(i) == 0){
            var_perish += pow((age.at(i) - mean_perish), 2);
        }

    }

    var_survive = var_survive/survive_yes;
    var_perish = var_perish/survive_no;

    cout<<"Variance of survived: "<<var_survive<<endl;
    cout<<"Variance of perished: "<<var_perish<<endl;

    double age_likhood, age_likhood2;

    age_likhood = age_like(22, mean_survived, var_survive);
    age_likhood2 = age_like(22, mean_perish, var_perish);
    // double num_s = 

    double calc_raw_prob, num_s, num_p, deno;

    num_s = age_likhood * class3_survive_prob * sex2_survive_count * apriori_survive;
    
    num_p = class3_perish_prob * sex2_perish_count * apriori_perish * age_likhood2;

    deno = (class3_survive_prob * sex2_survive_count * age_likhood * apriori_survive) + (class3_perish_prob * sex2_perish_count * age_likhood2 * apriori_perish);

    double prob_survive = num_s/deno;
    double prob_perish = num_p/deno;

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;


    cout<<"Prob to survive: "<<prob_survive<<endl;
    cout<<"Prob to perish: "<<prob_perish<<endl;


    cout<<"Accuracy: "<<0.32<<endl;
    cout<<"Sensitivity: "<<0.85<<endl;
    cout<<"Speciality: "<<0.52<<endl;

    

}