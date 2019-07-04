/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

void v2ct(int ibsp[], char fld[], char job, int n){
    
    //Variables
    int i,j,is;
    int istack[n];
    
    //Convert to Vienna
    if(job == 'V'){
        for(i=0;i<n;i++){
            if(ibsp[i] == 0)
                fld[i] = '.';
            else
                j = ibsp[i];
            if(j > i){
                fld[i] = '(';
                fld[j] = ')';
            }
            else{
                fld[i] = ')';
                fld[j] = '(';
            }
        }
    }
    
    //Convert to CT
    if(job == 'C'){
        is = 0;
        for(i=0;i<n;i++){
            ibsp[i] = 0;
            istack[i] = 0;
        }
        for(i=0;i<n;i++){
            if(fld[i] == '.')
                ibsp[i] = 0;
            else if(fld[i] == '('){
                istack[is] = i;
                is = is + 1;
            }
            else if(fld[i] == ')'){
                j = istack[is-1];
                ibsp[j] = i;
                ibsp[i] = j;
                is = is - 1;
            }
        }
    }
}
