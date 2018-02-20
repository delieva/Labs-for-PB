//
// Created by Александра Делиева on 20.02.18.
//

int find_even_index(const int *values, int length) {
    int sum2 = 0;
    for(int j = 0; j < length; j++){
        sum2 += values[j];
    }
    int sum1 = 0;
    for(int i = 0; i < length; i++){
        sum2 -= values[i];
        if(sum1 == sum2){
            return i;
        }
        sum1 += values[i];
    }
    return -1;
}