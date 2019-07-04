/*
 * Function: RANDOM (ISEED) 
 * Purpose: Generates a random number on the interval [0,1] given an
           integer seed.
 * Method: Efficent Fortran Programming, John Wiley and Sons, New York (1990)
         pp. 17-18 Library of Congress code QA76.73.F25 K78
 * Arguments:
           ISEED - Four byte integer seed.
 *  To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   random.h
 * Author: Nikhil
 *
 * Created on 18 June, 2019, 1:03 PM
 */

#ifndef RANDOM_H
#define RANDOM_H

double random(int iseed);

#endif /* RANDOM_H */

