import java.io.*;
import java.util.List;

public class FileIO {
    List<String[]> list;
    List<String> deleteList;

    public FileIO() {}

    public FileIO(List<String[]> list, List<String> deleteList) {
        this.list = list;
        this.deleteList  = deleteList;
    }

    void readFile(String inputFileName) {
        String line;

//        File inputFile = new File("./" + inputFileName);
//        File indexFile = new File("./" + indexFileName);

        File inputFile = new File(inputFileName);

        try {
            FileReader fr = new FileReader(inputFile);
            BufferedReader br = new BufferedReader(fr);

            while((line = br.readLine()) != null) {
                String[] array = line.split(",");

                list.add(array);
            }

//            FileReader fr2 = new FileReader(indexFile);
//            BufferedReader br2 = new BufferedReader(fr2);
//            int degree = 0;
//
//            while((line = br2.readLine()) != null) {
//                degree = Integer.parseInt(line);
//            }
//
//            return degree;

        } catch (IOException e) {
            e.printStackTrace();

//            return 0;
        }


    }

    void makePair(List<String[]> array, List<BPlusTree.KeyPair> inputPairs, int size) {
        for (int i = 0; i < size; i++) {
            BPlusTree.KeyPair pair = new BPlusTree.KeyPair(Integer.parseInt(array.get(i)[0]), Integer.parseInt(array.get(i)[1]));
            inputPairs.add(pair);
        }

    }

    void readDeletionFile(String filePath) {
        String line;

        File file = new File(filePath);

        try {
            BufferedReader br = new BufferedReader(new FileReader(file));
            while((line = br.readLine()) != null) {

                // test
//                int total = array.length;
//                for(int i = 0; i < total; i++) {
//                    System.out.println(array[i]);
//                }

                deleteList.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    void creation(String indexFileName, int degree) {
        File indexFile = new File("./" + indexFileName);

        try {
            FileWriter fw = new FileWriter(indexFile);
            fw.write(degree + "\n");
            fw.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
