package steganabara.filter;

import java.awt.image.BufferedImage;

public class FilterAlgorithms {

	public static BufferedImage applyMask(BufferedImage image, long mask, boolean amplify) {

		int amp = 0;
		for (; amp < 8; amp++)
			if ((mask & (1 << 7 - amp)) != 0 || (mask & (1 << 15 - amp)) != 0
					|| (mask & (1 << 23 - amp)) != 0) break;
		int width = image.getWidth();
		int height = image.getHeight();
		BufferedImage output = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++) {

				int rgb = image.getRGB(i, j) & (int) mask;
				if (amplify) rgb <<= amp;
				output.setRGB(i, j, rgb);

			} // end for
		return output;

	} // end applyMask

	public static BufferedImage colorMap(BufferedImage image, int color) {

		int width = image.getWidth();
		int height = image.getHeight();
		BufferedImage output = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++) {

				int rgb = image.getRGB(i, j);
				if (((rgb ^ color) & 0xFFFFFF) == 0) output.setRGB(i, j, 0x0000FF00);

			} // end for
		return output;

	} // end colorMap

} // end class
