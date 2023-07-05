package array;

public class SparseArray {
    public static void main(String[] args) {
        // 先有一个存在大量无效数据的二维数组
        int[][] src = new int[11][11];
        src[1][2] = 1;
        src[2][3] = 2;
        // 打印二维数组
        myPrint(src);
        // 记录下二维数组中有效元素的个数
        int cnt = 0;
        for (int[] row : src) {
            for (int val : row) {
                if (val != 0)
                    cnt++;
            }
        }
        // 创建压缩数组
        int[][] sparseArr = new int[cnt+1][3];
        sparseArr[0][0] = src.length;
        sparseArr[0][1] = src[0].length;
        sparseArr[0][2] = cnt;
        // 将数据进行压缩
        int top = 1;
        for (int i = 0; i < src.length; i++) {
            for (int j = 0; j < src[i].length; j++) {
                if (src[i][j] != 0) {
                    sparseArr[top][0] = i;
                    sparseArr[top][1] = j;
                    sparseArr[top][2] = src[i][j];
                    top++;
                }
            }
        }
        // 打印压缩数组
        myPrint(sparseArr);
        // 将压缩数组转为二维数组
        int[][] newArray = new int[sparseArr[0][0]][sparseArr[0][1]];
        for (int i = 1; i < sparseArr.length; i++) {
            newArray[sparseArr[i][0]][sparseArr[i][1]] = sparseArr[i][2];
        }
        // 打印二维数组
        myPrint(newArray);
    }
    public static void myPrint(int[][] arr) {
        for (int[] row : arr) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
}