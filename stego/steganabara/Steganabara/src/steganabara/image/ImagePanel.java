package steganabara.image;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Window;
import java.awt.image.BufferedImage;

import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JScrollPane;
import javax.swing.TransferHandler;

import steganabara.Stevironment;
import steganabara.menus.MenuMaker;

/**
 * Description: The panel to display an image
 * 
 * @author quangntenemy
 */

public class ImagePanel extends JComponent implements ImageContainer {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6411085477989824338L;
	private static final TransferHandler handler = new ImageFileTransferHandler();
	private BufferedImage image;
	private int width, height;
	private float zoom;

	/**
	 * Create an ImagePanel with the default size of 200x200
	 */

	public ImagePanel() {

		this(200, 200);

	} // end constructor

	/**
	 * Create an ImagePanel using the specified size
	 * 
	 * @param width
	 *            The panel's width
	 * @param height
	 *            The panel's height
	 */

	public ImagePanel(int width, int height) {

		this.width = width;
		this.height = height;
		zoom = 1;
		change();
		setTransferHandler(handler);

	} // end constructor

	/**
	 * Create an ImagePanel holding an Image
	 * 
	 * @param image
	 *            The image
	 */

	public ImagePanel(Image image) {

		setImage(image);
		setTransferHandler(handler);

	} // end constructor

	/**
	 * Get the image displayed in the panel
	 * 
	 * @return The image displayed in the panel
	 */

	public BufferedImage getImage() {

		return image;

	} // end getImage

	/**
	 * Set the image to be displayed in the panel
	 * 
	 * @param image
	 *            The image to be displayed in the panel
	 */

	public void setImage(Image image) {

		this.image = convert(image);
		width = image.getWidth(null);
		height = image.getHeight(null);
		zoom = 1;
		setComponentPopupMenu(MenuMaker.createImagePopupMenu(this));
		change();

	} // end setImage

	private void change() {

		Dimension dimension = new Dimension((int) (width * zoom), (int) (height * zoom));
		setPreferredSize(dimension);
		setMinimumSize(dimension);
		setMaximumSize(dimension);
		setSize(dimension);
		repaint();
		Window window = findTopWindow(this);
		if (window != null) window.pack();

	} // end change

	public static BufferedImage convert(Image image) {

		if (image instanceof BufferedImage) return (BufferedImage) image;
		int width = image.getWidth(null);
		int height = image.getWidth(null);
		BufferedImage bi = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
		Graphics bg = bi.getGraphics();
		bg.drawImage(image, 0, 0, null);
		bg.dispose();
		return bi;

	} // end convert

	public void paintComponent(Graphics g) {

		super.paintComponent(g);
		if (image != null)
			g.drawImage(image, 0, 0, (int) (width * zoom), (int) (height * zoom), this);

	} // end paintComponent

	public JComponent getComponent() {
		return this;
	}

	public float getZoom() {
		return zoom;
	}

	public void setZoom(float zoom) {
		this.zoom = zoom;
		change();
	}

	public int getRGB(int x, int y) {

		if (image != null && x >= 0 && x < width && y >= 0 && y < height)
			return image.getRGB(x, y);
		else
			return 0;

	} // end getRGB

	public static void showImageDialog(Component comp, String title, Image image) {

		Window owner = findTopWindow(comp);
		JDialog dialog = new JDialog(owner, title);
		ImagePanel panel = new ImagePanel(image);
		Stevironment.getInstance().registerImagePanel(panel);
		dialog.add(new JScrollPane(panel));
		dialog.setLocationRelativeTo(owner);
		dialog.pack();
		dialog.setVisible(true);

	} // end showImageDialog

	public static Window findTopWindow(Component comp) {

		if (comp == null) return null;
		if (comp instanceof Window)
			return (Window) comp;
		else
			return findTopWindow(comp.getParent());

	} // end findTopWindow

} // end class
