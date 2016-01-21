package steganabara.filter;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;

import javax.swing.JColorChooser;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import steganabara.image.ImageContainer;
import steganabara.image.ImagePanel;

public class ColorMapMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5516771725946656126L;
	private final ImageContainer imageContainer;

	public ColorMapMenuItem(ImageContainer imc) {

		super("Color Map", KeyEvent.VK_M);
		imageContainer = imc;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_M, ActionEvent.CTRL_MASK));
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		BufferedImage image = imageContainer.getImage();
		if (image == null) return;
		Color c = JColorChooser.showDialog(imageContainer.getComponent(), "Pick a color",
				Color.BLACK);
		if (c != null) showColorMapDialog(imageContainer.getComponent(), image, c.getRGB());

	} // end actionPerformed

	/**
	 * Filter the image with a color map
	 */
	public static void showColorMapDialog(Component owner, BufferedImage image, int color) {

		if (image == null) return;
		ImagePanel.showImageDialog(owner, "Color Map Filter", FilterAlgorithms.colorMap(image,
				color));

	} // end showColorMapDialog

} // end class
