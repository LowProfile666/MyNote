package recursion;

public class Maze {
    public static void main(String[] args) {
        // 迷宫地图
        int[][] map = new int[8][7];
        // 设置上下两端墙
        for (int i = 0; i < 7; i++) {
            map[0][i] = 1;
            map[7][i] = 1;
        }
        // 设置左右两端墙
        for (int i = 0; i < 7; i++) {
            map[i][0] = 1;
            map[i][6] = 1;
        }
        // 设置障碍墙
        map[3][1] = 1;
        map[3][2] = 1;
        // 打印迷宫地图
        System.out.println("原来的迷宫地图：");
        for (int[] row : map) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        isRun(map, 1, 1);
        System.out.println("走过后的迷宫地图：");
        for (int[] row : map) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
    /*
    用1表示墙，0表示路，2表示走过的路
     */
    public static boolean isRun(int[][] map, int i, int j) {
        if (map[6][5] == 2)     // 走到终点
            return true;
        else {
            if (map[i][j] == 0) {
                map[i][j] = 2;                         // 将走过的路标为2
                if (isRun(map, i+1, j))             // 往上
                    return true;
                else if (isRun(map, i+1, j))        // 往下
                    return true;
                else if (isRun(map, i, j-1))        // 往左
                    return true;
                else if (isRun(map, i, j+1))        // 往右
                    return true;
                else
                    return false;
            }else
                return false;
        }
    }
}
