/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "energy.h"
void tdangle5(int list[], float es){
    int i1,i2,i3;
    
    float au[4] = {-0.30e0,-0.10e0,-0.20e0,-0.20e0};
    float cg[4] = {-0.20e0,-0.30e0,-0.00e0,-0.00e0};
    float gc[4] = {-0.50e0,-0.30e0,-0.20e0,-0.10e0};
    float ua[4] = {-0.30e0,-0.30e0,-0.40e0,-0.20e0};
    float gu[4] = {-0.30e0,-0.10e0,-0.20e0,-0.20e0};
    float ug[4] = {-0.30e0,-0.30e0,-0.40e0,-0.20e0};
    
    // ! 5' (1) A X (3) 3' !
    // ! 3' (2) U       5' !

        i1 = list[0];
        i2 = list[1];
        i3 = list[2];

        if ( i1 == 1 && i2 == 4 ) es = es + au[i3];
        if ( i1 == 2 && i2 == 3 ) es = es + cg[i3];
        if ( i1 == 3 && i2 == 2 ) es = es + gc[i3];
        if ( i1 == 4 && i2 == 1 ) es = es + ua[i3];
        if ( i1 == 3 && i2 == 4 ) es = es + gu[i3];
        if ( i1 == 4 && i2 == 3 ) es = es + ug[i3];

}