package steganabara.menus;

import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JMenuItem;
import javax.swing.KeyStroke;
import javax.swing.TransferHandler;

import steganabara.image.ImageContainer;

public class CopyMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6330252213843559994L;
	private final ImageContainer container;

	public CopyMenuItem(ImageContainer container) {

		super("Copy", KeyEvent.VK_C);
		this.container = container;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK));
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		TransferHandler handler = container.getTransferHandler();
		if (handler != null)
			handler.exportToClipboard(container.getComponent(), Toolkit.getDefaultToolkit()
					.getSystemClipboard(), TransferHandler.COPY);

	} // end actionPerformed
} // end class
