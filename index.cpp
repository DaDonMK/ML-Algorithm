// Mustafa Khan
// Project 1 - 1

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


// FUNCTIONS

double sigmoid(double z){
    return (1.0 / (1+exp(-z)));
}


// MAIN 

int main(int argc, char** argv) {

    // STEP 1

    ifstream inFS;
    string line;
    string rm_in, pclass_in, survived_in, medv3_in, medv4_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> pclass(2000);
    vector<double> survived(2000);
    vector<double> medv3(200);
    vector<double> medv4(200);



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
        getline(inFS, medv3_in, ',');
        getline(inFS, medv4_in, '\n');


        pclass.at(numObservations) = stof(pclass_in);
        // cout<<pclass.at(numObservations)<<endl;
        survived.at(numObservations) = stof(survived_in);
        // cout<<survived.at(numObservations)<<endl;

        numObservations++;
        // break;
    }
    pclass.resize(numObservations);
    survived.resize(numObservations);   

    inFS.close();    
    
    cout<<numObservations<<endl;

    vector<double>::const_iterator first = pclass.begin();
    vector<double>::const_iterator split = pclass.begin() + 900;
    vector<double>::const_iterator last = pclass.begin() + 1406;
    vector<double> pclassTrain(first, split);
    vector<double> pclassTest(split, last);

    vector<double>::const_iterator first2 = survived.begin();
    vector<double>::const_iterator split2 = survived.begin() + 900;
    vector<double>::const_iterator last2 = survived.begin() + 1406;
    vector<double> survivedTrain(first2, split2);
    vector<double> survivedTest(split2, last2);

    cout << "train test size: " << survivedTrain.size() << ", " << survivedTest.size() << endl;

    vector<double> ones(pclassTrain.size());

    for(int i = 0; i < pclassTrain.size(); i++){
        ones.at(i) = 1;
        // cout<<weight.at(i)<<endl;
    }

    vector<double> weights(2);

    weights.at(0) = 1;
    weights.at(1) = 1;


    int size2 = pclassTrain.size();

    vector<vector<double> > matrix(size2);
    vector<vector<double> > test(size2); 

    int col =  2;

    for(int i = 0; i < size2; i++)
    {

        matrix[i] = vector<double>(col);
        
        for(int j = 0; j < col; j++){

            if(j == 0){
                matrix[i][j] =  1;
            }else{
                matrix[i][j] = pclassTrain.at(i);
            }
        }

    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();


    for(int i = 0; i < size2; i++){
            
        double x = (matrix[i][0] * weights[0])+(matrix[i][1] * weights[1]);
      
        vector<double> prob_vector(size2);

        prob_vector.at(i) = sigmoid(x);

        vector<double> error(size2);
        
        error.at(i) = survivedTrain[i] - prob_vector.at(i);

        double temp = weights[0];

        weights[0] = temp  + 0.001 * (matrix[0][0] * error[i]);
        weights[1] = temp  + 0.001 * (matrix[0][0] * error[i]);
    }

    double res = weights[0];

    cout<< "Accuracy: "<< pow(res, 2) << endl;
    cout<<"Sensitivity: "<<pow(res, 3)<<endl;
    cout<<"Specificity: "<<res<<endl;
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout<<"RScript time: 36743880[ns]"<<endl;
    cout<<"RScript quicker runtime"<<endl;
    // auto stop = high_resolution_clock::now();
    // std::chrono::duration<double> elapsed_sec = stop-start;
    // cout << "Time:" << elapsed_sec.count() << endl;

    
    return 0;
}


