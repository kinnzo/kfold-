/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   convert.h
! Subroutine: CONVERT (GSEQ,ISEQ,NN)
! 
! Purpose: Converts a character sequence of A C G U into numerical code.
!
! Method: Converts a nucleic acid sequence to the following numerical
!         code:
!
!              A = 1
!              C = 2
!              G = 3
!            T/U = 4
!
! Arguments:
!
!          GSEQ - (INPUT) Array of length NN containing the sequence
!                 of characters to be converted into numbers.
!          ISEQ - (OUTPUT) Array of length NN containing the sequence
!                 in the numerical code.
!            NN - Number of characters in the sequence.
!
 * Author: Nikhil
 *
 * Created on 18 June, 2019, 1:20 PM
 */

#ifndef CONVERT_H
#define CONVERT_H

void convert(char gseq[],int iseq[],int nn){
    for(int i=0;i<nn;i++){
        if(gseq[i]=='A' || gseq[i]=='a')
            iseq[i] = 1;
        else if(gseq[i]=='C' || gseq[i]=='c')
            iseq[i] = 2;
        else if(gseq[i]=='G' || gseq[i]=='g')
            iseq[i] = 3;
        else if(gseq[i]=='T' || gseq[i]=='t')
            iseq[i] = 4;
        if(gseq[i]=='U' or gseq[i]=='u')
            iseq[i] = 4;
    }
}


#endif /* CONVERT_H */

