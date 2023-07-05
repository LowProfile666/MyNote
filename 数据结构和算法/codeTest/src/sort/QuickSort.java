package sort;

import java.util.Arrays;

public class QuickSort {
    public static void main(String[] args) {
        int[] arr = {2, 3, 6, 3, 8, 9, 5, 7, 1};
        sort(arr, 0, arr.length-1);
        System.out.println(Arrays.toString(arr));
    }
    public static void sort(int[] arr, int left, int right) {
        int l = left;
        int r = right;
        int m = (l+r) / 2;
        int pivot = arr[m];
        while (l < r) {
            while (arr[l] < pivot) {
                l++;
            }
            while (arr[r] > pivot) {
                r--;
            }
            if (l >= r)
                break;
            int temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            if (arr[l] == pivot)
                r--;
            if (arr[r] == pivot)
                l++;
        }
        if (r == l) {
            l++;
            r--;
        }
        if (left < r)
            sort(arr, left, r);
        if (right > l)
            sort(arr, l, right);
    }
}