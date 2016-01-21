package steganabara.menus;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.KeyStroke;

import steganabara.image.ImageContainer;
import steganabara.image.ImageFileFilter;

public class SaveAsMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 3537486371523499744L;
	private final ImageContainer container;
	private final JFileChooser chooser;
	private static File path;

	public SaveAsMenuItem(ImageContainer container) {

		super("Save As", KeyEvent.VK_S);
		this.container = container;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, ActionEvent.CTRL_MASK));
		addActionListener(this);

		path = new File("Images/");
		chooser = new JFileChooser(path);
		chooser.setFileHidingEnabled(false);
		chooser.setFileFilter(new ImageFileFilter());

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		RenderedImage image = container.getImage();
		if (image == null) return;
		int returnVal = chooser.showSaveDialog(this);
		if (returnVal != JFileChooser.APPROVE_OPTION) return;
		path = chooser.getSelectedFile();

		if (path.exists())
			if (path.canWrite()) {

				returnVal = JOptionPane.showConfirmDialog(this, "Overwrite existing file?",
						"Overwrite", JOptionPane.OK_CANCEL_OPTION);
				if (returnVal != JOptionPane.OK_OPTION)
					return;
				else
					doWrite(image, path);

			} else
				JOptionPane.showMessageDialog(this, "File not writable!", "Error",
						JOptionPane.ERROR_MESSAGE);
		else
			doWrite(image, path);

	} // end actionPerformed

	protected void doWrite(RenderedImage image, File path) {

		if (!write(image, path))
			JOptionPane.showMessageDialog(null, "Could not write image!", "Error",
					JOptionPane.ERROR_MESSAGE);

	} // end doWrite

	public static boolean write(RenderedImage image, File path) {

		try {
			ImageIO.write(image, "png", new FileOutputStream(path));
			return true;
		} catch (IOException ex) {
			return false;
		}

	} // end write

} // end class
