import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static String inputFilePath = "/Users/leejiwon/Desktop/input.csv";
    private static String deleteFilePath = "/Users/leejiwon/Desktop/delete.csv";
    private static List<String[]> inputList = new ArrayList<>();
    private static List<String> deleteList = new ArrayList<>();
    private static List<BPlusTree.KeyPair> inputPairs = new ArrayList<>();
    private static int degree;

    public static void main(String[] args) {
        FileIO file = new FileIO(inputList, deleteList);
        BPlusTree tree = new BPlusTree( );

        String command;
        Scanner scanner = new Scanner(System.in);



        while (true) {
            System.out.println("Input Command (input \"java bptree -q\" to quit)");
            command = scanner.nextLine();
            String commandLang = command.split(" ")[2];

            if (commandLang.equals("-c")) {
                String indexFileName = command.split(" ")[3];
                degree = Integer.parseInt(command.split(" ")[4]);
                 System.out.println("Degree " + degree);

                 file.creation(indexFileName, degree);

//             test
                System.out.println("command creation complete");
            } else if (commandLang.equals("-i")) {

                String indexFileName = command.split(" ")[3];
                String inputFileName = command.split(" ")[4];

                file.readFile(inputFilePath);

                tree.degree = degree;


                int total = inputList.size();

                file.makePair(inputList, inputPairs, total);

                for (int i = 0; i < total; i++) {
                    tree.insertion(inputPairs.get(i));
                }

                //test
                System.out.println("command insertion complete");

            } else if (commandLang.equals("-d")) {

                String deleteFileName = command.split(" ")[4];

                file.readDeletionFile(deleteFilePath);

                for (int i = 0; i < deleteList.size(); i++) {
                    tree.deletion(Integer.parseInt(deleteList.get(i)));
                }
                System.out.println("command deletion complete");

            } else if (commandLang.equals("-s")) {

                int key = Integer.parseInt(command.split(" ")[4]);
                tree.singleSearch(key);

            } else if (commandLang.equals("-r")) {

                int start = Integer.parseInt(command.split(" ")[4]);
                int end = Integer.parseInt(command.split(" ")[5]);

                tree.rangeSearch(start, end);

            } else if(commandLang.equals("-q")) {
                break;
            }
            else {
                System.out.println("error");
            }
        }

    }
}
