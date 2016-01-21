package steganabara.menus;

import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.KeyStroke;

import steganabara.image.ImageContainer;
import steganabara.image.ImageFileFilter;

public class OpenMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6463086681112400443L;
	private final ImageContainer container;
	private final JFileChooser chooser;
	private static File path;

	public OpenMenuItem(ImageContainer container) {

		super("Open", KeyEvent.VK_O);
		this.container = container;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F3, 0));
		addActionListener(this);

		path = new File("Images/");
		chooser = new JFileChooser(path);
		chooser.setFileHidingEnabled(false);
		chooser.setFileFilter(new ImageFileFilter());

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		open();

	} // end actionPerformed

	/**
	 * Show a file chooser to open an image file
	 */
	public void open() {

		int returnVal = chooser.showOpenDialog(this);
		if (returnVal != JFileChooser.APPROVE_OPTION) return;

		path = chooser.getSelectedFile();
		try {

			Image image = ImageIO.read(path);
			if (image == null)
				System.err.println(image);
			else
				container.setImage(image);

		} catch (IOException e) {
			JOptionPane.showMessageDialog(this, "Could not read image!", "Error",
					JOptionPane.ERROR_MESSAGE);
		}

	} // end open

} // end class
