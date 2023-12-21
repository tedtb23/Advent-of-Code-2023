import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.FileReader;
public class FindSum {
    private Scanner fileScnr;
    
    FindSum(String fileName) {
        try {
            FileReader fRead = new FileReader(fileName);
            fileScnr = new Scanner(fRead);
        }catch(FileNotFoundException e) {
            System.out.println("lol");
            fileScnr = null;
        }
    }

    public int addSums() {
        int sum = 0;
        while(fileScnr.hasNextLine()) {
            sum += parseLine();
        }
        return sum;
    }

    private int parseLine() {
        String line = fileScnr.nextLine();
        int sum = 0;

        int i = 0, j = line.length() - 1;

        while(i < line.length()) {
            try{
                int x = Integer.parseInt(String.valueOf(line.charAt(i)));
                sum += x * 10;
                break;
            }catch(NumberFormatException e) {
                i++;
            }
        }

        while(j >= 0) {
            try {
                int x = Integer.parseInt(String.valueOf(line.charAt(j)));
                sum += x;
                break;
            } catch (NumberFormatException e) {
                j--;
            }

        }
        return sum;
    }
}
