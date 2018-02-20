//
// Created by Александра on 20.02.18.
//

void wave_sort(int arr[], int arr_size){
    // your code here
    int arr1[arr_size];
    for(int i = 0; i < arr_size; i++){
        arr1[i] = arr[i];
    }
    int hold = 0;
    for (int p = 0; p < arr_size - 1; p++){
        for (int j = p + 1; j < arr_size; j++){
            if (arr1[p] > arr1[j]){
                hold = arr1[j];
                arr1[j] = arr1[p];
                arr1[p] = hold;
            }
        }
    }
    for(int k = 0; k < arr_size; k++){
        if(k % 2 == 0){
            arr[k] = arr1[arr_size - 1 - k / 2];
        }
        else{
            arr[k] = arr1[(arr_size - 1) / 2 - k / 2];
        }
    }
}