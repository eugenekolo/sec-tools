package steganabara.histogram;

import java.awt.image.BufferedImage;
import java.util.Arrays;

/**
 * Description: The class to calculate the Histogram of an image
 * 
 * @author quangntenemy
 */

public final class Histogram {

	private static int[] histogram;
	private static final float[] GRAYSCALE = { 0.3f, 0.59f, 0.11f };
	private static final float[] RED = { 1, 0, 0 };
	private static final float[] GREEN = { 0, 1, 0 };
	private static final float[] BLUE = { 0, 0, 1 };

	/**
	 * Calculate the image histogram using a float array as coefficients for
	 * red, green and blue values
	 * 
	 * @param image
	 *            The source image
	 * @param mod
	 *            The array containing coefficients for red, green and blue
	 *            values
	 * @return An array representing the image histogram
	 */
	protected static int[] histogram(BufferedImage image, float[] mod) {

		histogram = new int[256];
		Arrays.fill(histogram, 0);
		int width = image.getWidth();
		int height = image.getHeight();

		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++) {

				int rgb = image.getRGB(i, j);
				int red = (rgb >> 16) & 0xFF;
				int green = (rgb >> 8) & 0xFF;
				int blue = rgb & 0xFF;
				int value = (int) (mod[0] * red + mod[1] * green + mod[2] * blue);
				histogram[value]++;

			} // end for

		return histogram;

	} // end histogram

	/**
	 * Calculate the image histogram using a specified mode
	 * 
	 * @param image
	 *            The source image
	 * @param mode
	 *            The histogram mode
	 * @return The image histogram
	 */
	public static int[] histogram(BufferedImage image, HistogramMode mode) {

		switch (mode) {

		case RED:
			return redHistogram(image);
		case GREEN:
			return greenHistogram(image);
		case BLUE:
			return blueHistogram(image);
		default:
			return grayscaleHistogram(image);

		} // end switch

	} // end histogram

	/**
	 * Calculate the histogram using the default mode: grayscale
	 * 
	 * @param image
	 *            The source image
	 * @return The grayscale histogram
	 */
	public static int[] histogram(BufferedImage image) {
		return grayscaleHistogram(image);
	}

	/**
	 * Calculate the grayscale histogram of an image
	 * 
	 * @param image
	 *            The source image
	 * @return The grayscale histogram
	 */
	public static int[] grayscaleHistogram(BufferedImage image) {
		return histogram(image, GRAYSCALE);
	}

	/**
	 * Calculate the red histogram of an image
	 * 
	 * @param image
	 *            The source image
	 * @return The red histogram
	 */
	public static int[] redHistogram(BufferedImage image) {
		return histogram(image, RED);
	}

	/**
	 * Calculate the green histogram of an image
	 * 
	 * @param image
	 *            The source image
	 * @return The green histogram
	 */
	public static int[] greenHistogram(BufferedImage image) {
		return histogram(image, GREEN);
	}

	/**
	 * Calculate the blue histogram of an image
	 * 
	 * @param image
	 *            The source image
	 * @return The grayscale histogram
	 */
	public static int[] blueHistogram(BufferedImage image) {
		return histogram(image, BLUE);
	}

} // end class
