package steganabara.image;

import java.awt.Image;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;

public class ImageTransferable implements Transferable {

	private final Image image;

	public ImageTransferable(Image image) {

		this.image = image;

	} // end constructor

	public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {

		return image;

	} // end getTransferData

	public DataFlavor[] getTransferDataFlavors() {

		return new DataFlavor[] { DataFlavor.imageFlavor };

	} // end getTransferDataFlavors

	public boolean isDataFlavorSupported(DataFlavor flavor) {

		return DataFlavor.imageFlavor.equals(flavor);

	} // end isDataFlavorSupported

} // end class
