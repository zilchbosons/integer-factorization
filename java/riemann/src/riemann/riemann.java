package riemann;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class riemann {
	private static String readFile(String file) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader (file));
		String         line = null;
		StringBuilder  stringBuilder = new StringBuilder();
		String         ls = System.getProperty("line.separator");

		try {
			while((line = reader.readLine()) != null) {
				stringBuilder.append(line);
				stringBuilder.append(ls);
			}

			return stringBuilder.toString();
		} finally {
			reader.close();
		}
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			String numStr = readFile("/home/subhendra/intfact-riemann/java/input.txt");
			System.out.println("Number Read was " + numStr);
			
;		} catch (IOException e) {

		}

	}
};
