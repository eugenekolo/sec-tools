package steganabara.image;

import java.awt.Image;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.JComponent;
import javax.swing.TransferHandler;

public class ImageFileTransferHandler extends TransferHandler {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7460978565204524729L;

	public boolean canImport(JComponent comp, DataFlavor[] transferFlavors) {

		for (int i = 0; i < transferFlavors.length; i++) {
			System.out.println(transferFlavors[i]);
			if (transferFlavors[i].equals(DataFlavor.imageFlavor)
					|| transferFlavors[i].equals(DataFlavor.stringFlavor)
					|| transferFlavors[i].equals(DataFlavor.javaFileListFlavor)) return true;
		}

		return false;

	} // end canImport

	public int getSourceActions(JComponent comp) {

		return COPY;

	} // end getSourceActions

	protected Transferable createTransferable(JComponent comp) {

		ImageContainer container = (ImageContainer) comp;
		return new ImageTransferable(container.getImage());

	} // end createTransferable

	public boolean importData(JComponent comp, Transferable t) {

		ImageContainer container = (ImageContainer) comp;
		return importImage(container, t) || importFileList(container, t) || importURI(container, t);

	} // end importData

	protected boolean importImage(ImageContainer container, Transferable t) {

		try {

			Image image = (Image) t.getTransferData(DataFlavor.imageFlavor);
			container.setImage(image);
			return true;

		} catch (UnsupportedFlavorException e) {

			return false;

		} catch (IOException e) {
			// TODO
			e.printStackTrace();
			return false;
		}

	} // end importImage

	@SuppressWarnings("unchecked")
	protected boolean importFileList(ImageContainer container, Transferable t) {

		try {

			List<File> list = (List<File>) t.getTransferData(DataFlavor.javaFileListFlavor);
			BufferedImage image = ImageIO.read(list.get(0));
			container.setImage(image);
			return true;

		} catch (UnsupportedFlavorException e) {

			return false;

		} catch (IOException e) {
			// TODO
			e.printStackTrace();
			return false;
		}

	} // end importFileList

	protected boolean importURI(ImageContainer container, Transferable t) {

		try {

			String s = (String) t.getTransferData(DataFlavor.stringFlavor);
			BufferedImage image = ImageIO.read(new URL(s.trim()));
			container.setImage(image);
			return true;

		} catch (UnsupportedFlavorException e) {

			return false;

		} catch (IOException e) {
			// TODO
			e.printStackTrace();
			return false;
		}

	} // end importURI

} // end class
