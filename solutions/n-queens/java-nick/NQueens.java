import java.util.*;

/**
 * Created by IntelliJ IDEA.
 * User: nickg
 * Date: 9/30/12
 * Time: 11:11 PM
 * To change this template use File | Settings | File Templates.
 */
public class NQueens {
    public static final int BOARD_SIZE = 8;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("SOLN\tCOLUMN\n #   1 2 3 4 5 6 7 8\n");
        int y = scanner.nextInt(), x = scanner.nextInt();

        doNQueens(x - 1, y - 1);
    }

    private static void doNQueens(int x, int y) {
        int[] takenRows = new int[BOARD_SIZE];
        for(int i=0; i < BOARD_SIZE; i++){
            takenRows[i] = -1;
        }
        takenRows[y] = x;

        Set<int[]> results = new LinkedHashSet<int[]>();
        recursiveHelper(takenRows, 0, x, results);
        printResults(results);
    }

    private static void recursiveHelper(int[] takenRows, int myColumn, int preDoneColumn, Set<int[]> results) {
        if(myColumn == BOARD_SIZE){
            // We got to the last column and things were placed appropriately!
            results.add(takenRows.clone());
        }

        if(myColumn == preDoneColumn){
            recursiveHelper(takenRows, myColumn+1, preDoneColumn, results);
            return;
        }

        Set<Integer> possiblePositions = validPlacements(takenRows, myColumn);
        for (Integer possiblePosition : possiblePositions) {
            // Place me here, go right, then remove my placement
            takenRows[possiblePosition] = myColumn;
            recursiveHelper(takenRows, myColumn + 1, preDoneColumn, results);
            takenRows[possiblePosition] = -1;
        }
    }

    private static Set<Integer> validPlacements(int[] takenRows, int column) {
        Set<Integer> rval = build0toN();
        for(int i = 0; i < BOARD_SIZE; i++){
            int takenRow = takenRows[i];
            if(takenRow > -1){
                // Row i is occupied by another queen
                rval.remove(i);

                // We determine the x position distance from this queen to our current row
                // and delete the corresponding rows (diagonally)
                int distance = Math.abs(takenRow - column);
                if(i - distance >= 0){
                    rval.remove(i - distance);
                }
                if(i + distance < BOARD_SIZE){
                    rval.remove(i + distance);
                }
            }
        }
        return rval;

    }

    private static void printResults(Set<int[]> results) {
        int goodResults = 0;
        for (int[] result : results) {
            System.out.print("" + ++goodResults + "   ");
            int[] columnMajor = new int[BOARD_SIZE];
            for (int i = 0, resultLength = result.length; i < resultLength; i++) {
                int takenRow = result[i];
                columnMajor[takenRow] = i;
            }
            for (int i : columnMajor) {
                System.out.print(" " + (i + 1));
            }
            System.out.println();
        }
    }

    private static TreeSet<Integer> build0toN() {
        TreeSet<Integer> integers = new TreeSet<Integer>();
        for(int i = 0; i < BOARD_SIZE; i++){
            integers.add(i);
        }
        return integers;
    }

}
