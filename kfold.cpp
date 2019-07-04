/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Nikhil
 *
 * Created on 17 June, 2019, 12:07 PM
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "rnavar.h"
#include "random.h"
#include "convert.h"


using namespace std;

/*  
 
*/
int main(int argc, char** argv) {
    srand(120);
    cout<<"[INFO] Parsing the Arguments"<<endl;
    char seq[1000];
    seq[0] = 'A';
    seq[1] = 'G';
    seq[2] = 'C';
    seq[3] = '\0';
    cout<<seq;
    string st = "ABSD";
    cout<<st;
    cout<<mxnt<<endl;
    cout<<em<<" "<<eau<<" "<<es<<endl;
    cout<<gcons;
    for(int i=0;i<5;i++)
    cout<<endl<<random(6200);
    char gseq[] = {'A','G','C','U'};
    int iseq[4];
    convert(gseq,iseq,4);
    for(int i=0;i<4;i++)
        cout<<endl<<iseq[i];
    
    for(int i=0;i<4;i++)
        cout<<endl<<((double(rand())/RAND_MAX));
    readdata();
    cout<<endl<<eaup[0][3];
    setupnuc(10);
    cout<<endl<<"PNUC: "<<pnuc[5];
    return 0;
}

