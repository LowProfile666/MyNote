package sort;

import java.util.Arrays;

public class BubblingSort {
    public static void main(String[] args) {
        int[] arr = {5, 4, 3, 6, 2, 1};
        for (int i = 0; i < arr.length-1; i++) {
            for (int j = 0; j < arr.length-i-1; j++) {
                if (arr[j] > arr[j+1]) {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
        System.out.println(Arrays.toString(arr));
    }
}
