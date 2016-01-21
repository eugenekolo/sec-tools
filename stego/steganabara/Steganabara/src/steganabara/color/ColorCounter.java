package steganabara.color;

import java.awt.image.BufferedImage;
import java.util.Hashtable;

public final class ColorCounter {

	public static Hashtable<Integer, Integer> count(BufferedImage image) {

		Hashtable<Integer, Integer> table = new Hashtable<Integer, Integer>();
		int width = image.getWidth();
		int height = image.getHeight();

		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++) {

				int rgb = image.getRGB(i, j);
				table.put(rgb, table.containsKey(rgb) ? table.get(rgb) + 1 : 1);

			} // end for

		return table;

	} // end count

} // end class
