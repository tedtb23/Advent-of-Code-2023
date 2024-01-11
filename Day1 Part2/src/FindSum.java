import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class FindSum {
    public int addSums(Scanner scnr) {
        int sum = 0;
        if(scnr != null)
            while(scnr.hasNextLine()) {
                sum += parseLine(scnr);
            }
        return sum;
    }

    private int parseLine(Scanner scnr) {
        String line = scnr.nextLine();
        int sum = 0;

        //use lookup instead
        Pattern s = Pattern.compile("(one|two|three|four|five|six|seven|eight|nine|ne|wo|hree|our|ive|ix|even|ight|ine)");
        Pattern i = Pattern.compile("[1-9]");
        Matcher ms = s.matcher(line);
        Matcher mi = i.matcher(line);

        if(ms.find() && mi.find()) {
            String digitStr = ms.group();
            int digit = 0;

            if(ms.start() > mi.start()) {
                digit = Integer.parseInt(mi.group());
            }else {
                digit = getDigit(digitStr);
            }
            sum += digit * 10;
            ms.reset();
            mi.reset();
        }else {
            ms.reset();
            mi.reset();
            int digit = 0;

            if(ms.find()) {
                String digitStr = ms.group();
                digit = getDigit(digitStr);
            }else if(mi.find()){
                digit = Integer.parseInt(mi.group());
            }
            sum += digit * 10;
            ms.reset();
            mi.reset();
        }

        if(ms.find() || mi.find()) {
            ms.reset();
            mi.reset();
            String digitStr = "";
            int digitInt = 0;
            int digit = 0;
            int sIdx = -1;
            int iIdx = -1;
            while(ms.find()) {
                digitStr = ms.group();
                sIdx = ms.start();
            }
            while(mi.find()) {
                digitInt = Integer.parseInt(mi.group());
                iIdx = mi.start();
            }

            if(sIdx < iIdx) {
                digit = digitInt;
            }else {
                digit = getDigit(digitStr);
            }
            sum += digit;
        }
        return sum;
    }

    private int getDigit(String digitStr) {
        return switch(digitStr) {
            case "one", "ne" -> 1;
            case "two", "wo" -> 2;
            case "three", "hree" -> 3;
            case "four", "our" -> 4;
            case "five", "ive" -> 5;
            case "six", "ix" -> 6;
            case "seven", "even" -> 7;
            case "eight", "ight" -> 8;
            case "nine", "ine" -> 9;
            default -> 0;
        };
    }
}
