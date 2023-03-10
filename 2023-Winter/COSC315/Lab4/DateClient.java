/**
 * Client program requesting current date from server.
 *
 * Figure 3.22
 *
 * @author Silberschatz, Gagne and Galvin
 * Operating System Concepts  - Eighth Edition
 */

import java.net.*;
import java.io.*;

public class DateClient
{
    public static void main(String[] args)  {
        try {
            // this could be changed to an IP name or address other than the localhost
            Socket sock = new Socket("127.0.0.1", 7777);
            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));

            int localPort = sock.getLocalPort();
            System.out.println(localPort);

            String line;
            while( (line = bin.readLine()) != null)
                System.out.println(line);

            sock.close();
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}