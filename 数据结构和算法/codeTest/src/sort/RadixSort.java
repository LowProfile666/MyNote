package sort;

import java.util.Arrays;

public class RadixSort {
    public static void main(String[] args) {
        int[] array = {23, 4, 54, 76, 345, 64, 244, 9, 78, 55, 34};
        System.out.println("排序前：" + Arrays.toString(array));
        radixSort(array);
        System.out.println("排序后：" + Arrays.toString(array));
    }
    public static void radixSort(int[] array) {
        int[][] bucket = new int[array.length][array.length];
        int[] aid = new int[array.length];
        // 比较个位数
        // 先按个位数放入桶内
        for (int i = 0; i < array.length; i++) {
            int j = array[i] % 10;
            bucket[j][aid[j]++] = array[i];
        }
        // 再取出来
        int idx = 0;
        for (int i = 0; i < aid.length; i++) {
            if (aid[i] != 0) {
                int j = 0;
                for ( ; j < aid[i]; j++)
                    array[idx++] = bucket[i][j];
                aid[i] = 0;
            }
        }
        System.out.println("array: " + Arrays.toString(array));  // array: [23, 4, 54, 64, 244, 34, 345, 55, 76, 78, 9]
        // 比较十位数
        // 先按十位放入桶内
        for (int i = 0; i < array.length; i++) {
            int j = array[i] / 10 % 10;
            bucket[j][aid[j]++] = array[i];
        }
        // 再取出来
        idx = 0;
        for (int i = 0; i < aid.length; i++) {
            if (aid[i] != 0) {
                int j = 0;
                for ( ; j < aid[i]; j++)
                    array[idx++] = bucket[i][j];
                aid[i] = 0;
            }
        }
        System.out.println("array: " + Arrays.toString(array));  // array: [4, 9, 23, 34, 244, 345, 54, 55, 64, 76, 78]
        // 比较百位
        // 先按百位放入桶内
        for (int i = 0; i < array.length; i++) {
            int j = array[i] / 100;
            bucket[j][aid[j]++] = array[i];
        }
        // 再取出来
        idx = 0;
        for (int i = 0; i < aid.length; i++) {
            if (aid[i] != 0) {
                for ( int j = 0; j < aid[i]; j++)
                    array[idx++] = bucket[i][j];
                aid[i] = 0;
            }
        }
        System.out.println("array: " + Arrays.toString(array));  // array: [4, 9, 23, 34, 54, 55, 64, 76, 78, 244, 345]
    }

}
