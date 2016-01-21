package steganabara.menus;

import java.awt.Toolkit;
import java.awt.datatransfer.Transferable;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import steganabara.image.ImageContainer;

public class PasteMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2944396828649198603L;
	private final ImageContainer container;

	public PasteMenuItem(ImageContainer container) {

		super("Paste", KeyEvent.VK_P);
		this.container = container;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V, ActionEvent.CTRL_MASK));
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		Transferable t = Toolkit.getDefaultToolkit().getSystemClipboard().getContents(this);
		container.getTransferHandler().importData(container.getComponent(), t);

	} // end actionPerformed

} // end class
