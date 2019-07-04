/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"

void tloop(int list[],int el){
    int i;
    char cl[6];
    
    float ener[30] = {-3.00e0,-3.00e0,-3.00e0,-3.00e0, 
                -3.00e0,-3.00e0,-3.00e0,-3.00e0,-3.00e0,-2.50e0, 
                -2.50e0,-2.50e0,-2.50e0,-2.50e0,-2.00e0,-2.00e0, 
                -2.00e0,-2.00e0,-2.00e0,-1.50e0,-1.50e0,-1.50e0, 
                -1.50e0,-1.50e0,-1.50e0,-1.50e0,-1.50e0,-1.50e0, 
                -1.50e0,-1.50e0};
    char cseq[7][30] = {'GGGGAC','GGUGAC','CGAAAG','GGAGAC',  
               'CGCAAG','GGAAAC','CGGAAG','CUUCGG','CGUGAG','CGAAGG',  
               'CUACGG','GGCAAC','CGCGAG','UGAGAG','CGAGAG','AGAAAU',  
               'CGUAAG','CUAACG','UGAAAG','GGAAGC','GGGAAC','UGAAAA',  
               'AGCAAU','AGUAAU','CGGGAG','AGUGAU','GGCGAC','GGGAGC',  
               'GUGAAC','UGGAAA'};
    
    
    //    !      1 2 3 4 5 6      !
    //    !  5'  A W X Y Z U   3' !
    //    !        L O O P        !

    for(int i=0;i<6;i++){
        if ( list[i] == 1 ) cl[i] = 'A';
          if ( list[i] == 2 ) cl[i] = 'C';
          if ( list[i] == 3 ) cl[i] = 'G';
          if ( list[i] == 4 ) cl[i] = 'U';
    }
    //Here is  a write statement
    std::cout<<cl;
    for(i=0;i<30;i++){
        if(cseq[i] == cl) el = el + ener[i];
    }
}