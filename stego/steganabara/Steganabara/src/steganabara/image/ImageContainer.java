package steganabara.image;

import java.awt.Image;
import java.awt.image.BufferedImage;

import javax.swing.JComponent;
import javax.swing.TransferHandler;

public interface ImageContainer {

	public BufferedImage getImage();

	public void setImage(Image image);

	public JComponent getComponent();

	public TransferHandler getTransferHandler();

	public float getZoom();

	public void setZoom(float zoom);

	public int getRGB(int x, int y);

} // end interface
