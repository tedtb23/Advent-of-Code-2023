public class Main {
    public static void main(String[] args) {
        FindSum fs = new FindSum("Calibration.txt");
        int sum = fs.addSums();
        System.out.println(sum);
    }
}