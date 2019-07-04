/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"

void tstackh(int list[], float es){
    int i1, i2, i3, i4;
    
    float au[4][4] = {{ -0.30e00,  -0.50e00,  -0.30e00,  -0.30e00 },                                                                                                                                
        { -0.10e00,  -0.20e00,  -0.15e01,  -0.20e00 },                                                                                                                                 
        { -0.11e01,  -0.12e01,  -0.20e00,   0.20e00 },                                                                                                                                 
        { -0.30e00,  -0.30e00,  -0.60e00,  -0.11e01 }};
    
    float cg[4][4] = {{ -0.15e01,  -0.15e01,  -0.14e01,  -0.18e01 },                                                                                                                                
{ -0.10e01,  -0.90e00,  -0.29e01,  -0.80e00 },                                                                                                                                 
{ -0.22e01,  -0.20e01,  -0.16e01,  -0.11e01 },                                                                                                                                 
{ -0.17e01,  -0.14e01,  -0.18e01,  -0.20e01 }};  
    
    float gc[4][4] = {{ -0.11e01,  -0.15e01,  -0.13e01,  -0.21e01 }, 
{ -0.11e01,  -0.70e00,  -0.24e01,  -0.50e00 }, 
{ -0.24e01,  -0.29e01,  -0.14e01,  -0.12e01 }, 
{ -0.19e01,  -0.10e01,  -0.22e01,  -0.15e01 }}; 
    
    float ua[4][4] = {{ -0.50e00,  -0.30e00,  -0.60e00,  -0.50e00 }, 
{ -0.20e00,  -0.10e00,  -0.12e01,  -0.00e00 }, 
{ -0.14e01,  -0.12e01,  -0.70e00,  -0.20e00 }, 
{ -0.30e00,  -0.10e00,  -0.50e00,  -0.80e00 }};
    
    float gu[4][4] = {{  0.20e00,  -0.50e00,  -0.30e00,  -0.30e00 }, 
{ -0.10e00,  -0.20e00,  -0.15e01,  -0.20e00 }, 
{ -0.90e00,  -0.11e01,  -0.30e00,  -0.00e00 }, 
{ -0.30e00,  -0.30e00,  -0.40e00,  -0.11e01 }};
    
    float ug[4][4] = {{ -0.50e00,  -0.30e00,  -0.60e00,  -0.50e00 }, 
{ -0.20e00,  -0.10e00,  -0.17e01,  -0.00e00 }, 
{ -0.80e00,  -0.12e01,  -0.30e00,  -0.70e00 }, 
{ -0.60e00,  -0.10e00,  -0.60e00,  -0.80e00 }};
    
    //  ! 5' (1) A X (3) 3' !
    //  ! 3' (2) U Y (4) 5' !
    
        i1 = list[0];
        i2 = list[1];
        i3 = list[2];
        i4 = list[3];

        if( i1 == 1 && i2 == 4 ) es = es + au[i3][i4];
        if( i1 == 2 && i2 == 3 ) es = es + cg[i3][i4];
        if( i1 == 3 && i2 == 2 ) es = es + gc[i3][i4];
        if( i1 == 4 && i2 == 1 ) es = es + ua[i3][i4];
        if( i1 == 3 && i2 == 4 ) es = es + gu[i3][i4];
        if( i1 == 4 && i2 == 3 ) es = es + ug[i3][i4];
}