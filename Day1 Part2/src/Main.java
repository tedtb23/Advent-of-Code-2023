import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

import java.io.FileReader;
import java.io.FileNotFoundException;

public class Main {
    public static void main(String[] args) {
        try {
            FileReader fRead = new FileReader("Calibration.txt");
            Scanner fileScnr = new Scanner(fRead);
            FindSum fs = new FindSum();
            int sum = fs.addSums(fileScnr);
            System.out.println(sum);
        }catch(FileNotFoundException e) {
            System.out.println("File not Found");
            System.exit(-1);
        }
    }
}