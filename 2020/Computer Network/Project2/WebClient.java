package project2;

import java.io.* ;
import java.net.* ;
import java.util.* ;

public class WebClient {

    public static void main(String[] args) throws IOException{
        WebClient client = new WebClient();
        int menu;
        String url;
        Scanner scanner = new Scanner(System.in);

        while(true) {
        	System.out.print("Select command (1:GET, 2:POST, 0:exit) : ");
        	menu = scanner.nextInt();
            scanner.nextLine();
            System.out.println();
            System.out.print("Insert URL : ");
            url = scanner.nextLine();
            System.out.println();
            if(menu == 1){
                String s = client.getWebContentByGet(url);
                System.out.println(s);
            } else if(menu == 2){
                System.out.print("Insert data : ");
                String data = scanner.nextLine();
                String s = client.getWebContentByPost(url, data);
                System.out.println("Received message : "+s);
            } else if(menu == 0){
            	System.out.println("Bye!");
            	break;
            } else {
            	System.out.println("Wrong Input");
            }
        }
    }

    public String getWebContentByPost(String urlString,String data) throws IOException {
        return getWebContentByPost(urlString, data,"UTF-8", 5000);//iso-8859-1
    }

    public String getWebContentByGet(String urlString) throws IOException {
        return getWebContentByGet(urlString, "iso-8859-1", 5000);
    }

    public String getWebContentByGet(String urlString, final String charset, int timeout) throws IOException {
        if(urlString == null || urlString.length() == 0){
            return null;
        }

        urlString = (urlString.startsWith("http://") || urlString.startsWith("https://")) ? urlString : ("http://"+urlString).intern();

        URL url = new URL(urlString);

        HttpURLConnection conn = (HttpURLConnection) url.openConnection();

        conn.setRequestMethod("GET");
        conn.setRequestProperty("User-Agent", "2019000982/JIWONLEE/WebClient/ComNet");
        conn.setRequestProperty("Accept", "text/html");
        conn.setConnectTimeout(timeout);
        try{
            if(conn.getResponseCode() != HttpURLConnection.HTTP_OK){
                return null;
            }
        }
        catch (IOException e){
            e.printStackTrace();
            return null;
        }

        InputStream input=conn.getInputStream();
        BufferedReader reader=new BufferedReader(new InputStreamReader(input, charset));
        String line = null;
        StringBuffer sb = new StringBuffer();
        while ((line=reader.readLine())!= null){
            sb.append(line).append("\r\n");
        }
        if(reader != null){
            reader.close();
        }
        if(conn != null){
            conn.disconnect();
        }
        return sb.toString();
    }

    public String getWebContentByPost(String urlString, String data, final String charset, int timeout) throws IOException{
        if(urlString == null || urlString.length() == 0){
            return null;
        }

        urlString = (urlString.startsWith("http://") || urlString.startsWith("https://")) ? urlString : ("http://"+urlString).intern();

        URL url = new URL(urlString);

        HttpURLConnection conn = (HttpURLConnection) url.openConnection();

        conn.setDoOutput(true);
        conn.setDoInput(true);
        conn.setRequestMethod("POST");

        conn.setUseCaches(false);
        conn.setInstanceFollowRedirects(true);

        conn.setRequestProperty("Content-Type", "text/xml;charset=UTF-8");
        conn.setRequestProperty("User-Agent", "2019000982/JIWONLEE/WebClient/ComNet");
        conn.setRequestProperty("Accept", "text/html");
        conn.setConnectTimeout(timeout);
        conn.connect();
        DataOutputStream out = new DataOutputStream(conn.getOutputStream());

        byte[] content = data.getBytes("UTF-8");
        out.write(content);
        out.flush();
        out.close();

        try {
            if(conn.getResponseCode() != HttpURLConnection.HTTP_OK){
                return null;
            }
        }
        catch (IOException e){
            e.printStackTrace();
            return null;
        }
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
        StringBuffer sb = new StringBuffer();
        while ((line = reader.readLine()) != null){
            sb.append(line).append("\r\n");
        }
        if(reader != null){
            reader.close();
        }
        if(conn != null){
            conn.disconnect();
        }
        return sb.toString();
    }
}