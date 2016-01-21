package steganabara.color;

import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JCheckBoxMenuItem;
import javax.swing.KeyStroke;

public class ColorExplorerMenuItem extends JCheckBoxMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1464674940334416793L;
	private final Window window;

	public ColorExplorerMenuItem(Window window) {

		super("Color Explorer");
		this.window = window;
		setMnemonic(KeyEvent.VK_E);
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E, ActionEvent.CTRL_MASK));
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		window.setVisible(isSelected());

	} // end actionPerformed

} // end class
