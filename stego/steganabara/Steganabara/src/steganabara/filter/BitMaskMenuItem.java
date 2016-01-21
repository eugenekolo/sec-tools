package steganabara.filter;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;

import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import steganabara.image.ImageContainer;
import steganabara.image.ImagePanel;

public class BitMaskMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -699316866251078223L;
	private final ImageContainer imageContainer;

	public BitMaskMenuItem(ImageContainer imc) {

		super("Bit Mask", KeyEvent.VK_B);
		imageContainer = imc;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_B, ActionEvent.CTRL_MASK));
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		BufferedImage image = imageContainer.getImage();
		if (image == null) return;
		BitMaskOptions options = BitMaskDialog.showBitMaskDialog(imageContainer.getComponent(),
				"Bit Mask Filter");
		if (options != null) showBitMaskDialog(imageContainer.getComponent(), image, options);

	} // end actionPerformed

	/**
	 * Filter the image with a bit mask
	 */
	public static void showBitMaskDialog(Component owner, BufferedImage image,
			BitMaskOptions options) {

		if (image == null) return;
		ImagePanel.showImageDialog(owner, "Bit Mask Filter", FilterAlgorithms.applyMask(image,
				options.getMask(), options.isAmplify()));

	} // end showBitMaskDialog

} // end class
