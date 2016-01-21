package steganabara.histogram;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.JComponent;

/**
 * Description: The panel to display the image histogram in a nice way
 * 
 * @author quangntenemy
 */

public class HistogramPanel extends JComponent {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7042552569741169352L;
	private int[] histogram;
	private HistogramMode mode;

	/**
	 * Create a default panel for grayscale histogram
	 */
	public HistogramPanel() {

		this(HistogramMode.GRAYSCALE);

	} // end default constructor

	/**
	 * Create a panel for histogram with a parameter to set the histogram mode
	 * 
	 * @param mode
	 *            The histogram mode
	 * @see #setMode
	 */
	public HistogramPanel(HistogramMode mode) {

		setMode(mode);

	} // end constructor

	/**
	 * Create a panel for an image histogram
	 * 
	 * @param image
	 *            The source image
	 */
	public HistogramPanel(BufferedImage image) {

		this(image, HistogramMode.GRAYSCALE);

	} // end constructor

	/**
	 * Create a panel for an image histogram with a parameter to set the
	 * histogram mode
	 * 
	 * @param image
	 *            The source image
	 * @param mode
	 *            The histogram mode
	 * @see #setMode
	 */
	public HistogramPanel(BufferedImage image, HistogramMode mode) {

		setMode(mode);
		setPreferredSize(new Dimension(256, 110));
		setImage(image);

	} // end constructor

	/**
	 * Set the mode of the histogram
	 * 
	 * @param mode
	 *            The histogram mode
	 */
	public void setMode(HistogramMode mode) {

		this.mode = mode;

	} // end setMode

	/**
	 * Set the histogram source image
	 * 
	 * @param image
	 *            The source image
	 */
	public void setImage(BufferedImage image) {

		histogram = Histogram.histogram(image, mode);

	} // end setImage

	/**
	 * GUI method to paint the panel
	 * 
	 * @see javax.swing.JPanel#paintComponent
	 */
	public void paintComponent(Graphics g) {

		super.paintComponent(g);
		if (histogram != null) {

			int max = 0;

			for (int i = 0; i < 256; i++) {

				switch (mode) {

				case RED:
					g.setColor(new Color(i, 0, 0));
					break;
				case GREEN:
					g.setColor(new Color(0, i, 0));
					break;
				case BLUE:
					g.setColor(new Color(0, 0, i));
					break;
				default:
					g.setColor(new Color(i, i, i));
					break;

				} // end switch
				g.drawLine(i, 104, i, 109);
				if (histogram[i] > max) max = histogram[i];

			} // end for

			g.setColor(Color.BLACK);
			for (int i = 0; i < 256; i++) {

				int percent = histogram[i] * 100 / max;
				if (percent > 0) g.drawLine(i, 100, i, 100 - percent);

			} // end for

		} // end if

	} // end paintComponent

} // end class
