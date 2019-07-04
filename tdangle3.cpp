/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "energy.h"

void tdangle3(int list[], float es){
    int i1,i2,i3;
    
    float au[4] = {-0.80e0,-0.50e0,-0.80e0,-0.60e0};
    float cg[4] = {-1.70e0,-0.80e0,-1.70e0,-1.20e0};
    float gc[4] = {-1.10e0,-0.40e0,-1.30e0,-0.60e0};
    float ua[4] = {-0.70e0,-0.10e0,-0.70e0,-0.10e0};
    float gu[4] = {-0.80e0,-0.50e0,-0.80e0,-0.60e0};
    float ug[4] = {-0.70e0,-0.10e0,-0.70e0,-0.10e0};
    
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

/*Conversion Code to Run in Fortran
 
 * 
 * 
Program Hello

IMPLICIT NONE
INTEGER :: i,j,i1,i2,i3,i4
REAL :: au(96,16),cg(96,16),gc(96,16)
REAL :: ua(96,16),gu(96,16),ug(96,16)

!Add array data here
 
 write(*,"(A)",advance="no") "{"
do, i=1,96
    write(*,"(A)",advance="no") "{"
    do, j=1,16
        !print *,au(i,j)
        write(*,"(3f5.2)",advance="no") ug(i,j)
        if(j /= 16) write(*,"(A)",advance="no") ", "
    ENDDO
    if(i /= 96) THEN
        write(*,*) "}, "
    else 
        write(*,*) "}};"
    ENDIF
ENDDO
End Program Hello
 */