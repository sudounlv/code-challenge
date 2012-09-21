import java.util.*;

public class PasswordGrid {

    private static final int NUMBER_OF_COLUMNS = 5;
    private static final int NUMBER_OF_STRINGS = 6;
    private static final String INVALID_RESPONSE = "NO";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int count = scanner.nextInt();

        for(int i = 0; i < count; i++){
            int position = scanner.nextInt();
            System.out.println(doString(commonColumns(scanner), position - 1 ));
        }

    }

    private static String doString(List<SortedSet<Character>> commonColumns, int position) {
        // If any column in the two grids had *no* matching elements, there can't be any candidate passwords
        for (SortedSet<Character> commonColumn : commonColumns) {
            if(commonColumn.isEmpty()) return INVALID_RESPONSE;
        }

        // We construct here a multiplicative list of the count all of the possible password strings
        // from right to left.
        // [2,3,2,3,4] => [72,24,12,4]
        // The presumption being that, say, the 100th string in order would come after the first 72 strings of length 4,
        // so we subtract 72 from 100 and take the second character in column 1.
        Integer[] totalsBehindMe = new Integer[NUMBER_OF_COLUMNS - 1];

        // Gather up the list of underneath-me-totals
        int runningTotal = 1;
        for(int i = NUMBER_OF_COLUMNS - 2; i >= 0; i--){
            runningTotal *= commonColumns.get(i+1).size();
            totalsBehindMe[i] = runningTotal;
        }

        // If the total number of all possible passwords from the grids
        // Is not large enough to match the one we want, then k > size and return 'NO'
        if(runningTotal * commonColumns.get(0).size() <= position){
            return INVALID_RESPONSE;
        }

        StringBuilder theOne = new StringBuilder();

        //Use the magic array we created before to select the position on each column
        //that this password takes up
        for(int i = 0; i < NUMBER_OF_COLUMNS - 1; i++){
            int myPosition = position / totalsBehindMe[i];
            position = position % totalsBehindMe[i];
            theOne.append(commonColumns.get(i).toArray()[myPosition]);
        }
        theOne.append(commonColumns.get(NUMBER_OF_COLUMNS - 1).toArray()[position]);

        return theOne.toString();
    }

    /**
     * Read in both grids, and perform an intersection operation on each column
     * to whittle the 2 grids down to a list of sets of common characters, one set per column.
     */
    private static List<SortedSet<Character>> commonColumns(Scanner scanner) {
        List<SortedSet<Character>> firstGrid = getSixThings(scanner);
        List<SortedSet<Character>> secondGrid = getSixThings(scanner);

        for(int i = 0; i < NUMBER_OF_COLUMNS; i++){
            firstGrid.get(i).retainAll(secondGrid.get(i));
        }

        return firstGrid;
    }

    private static List<SortedSet<Character>> getSixThings(Scanner scanner) {
        List<SortedSet<Character>> firsts = new ArrayList<SortedSet<Character>>(NUMBER_OF_COLUMNS);

        for(int i = 0; i < NUMBER_OF_COLUMNS; i++){
            firsts.add(new TreeSet<Character>());
        }

        for(int i = 0; i < NUMBER_OF_STRINGS; i++){
            String element = scanner.next().trim().toUpperCase();
            for(int j = 0; j < NUMBER_OF_COLUMNS; j++){
                firsts.get(j).add(element.charAt(j));
            }
        }
        return firsts;
    }
}
