package steganabara.color;

import java.awt.Component;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;

import javax.swing.JDialog;
import javax.swing.JMenuItem;
import javax.swing.JScrollPane;
import javax.swing.KeyStroke;

import steganabara.TableSorter;
import steganabara.image.ImageContainer;

public class ColorTableMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 8768998584978164773L;
	private final ImageContainer imageContainer;

	public ColorTableMenuItem(ImageContainer imc) {

		super("Color Table", KeyEvent.VK_T);
		imageContainer = imc;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_T, ActionEvent.CTRL_MASK));
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		showColorTable(imageContainer.getComponent(), imageContainer.getImage());

	} // end actionPerformed

	/**
	 * Show the color table
	 */
	public static void showColorTable(Component owner, BufferedImage image) {

		if (image == null) return;
		TableSorter sorter = new TableSorter(new ColorTableModel(image));
		ColorTable table = new ColorTable(sorter, image);
		sorter.setTableHeader(table.getTableHeader());
		JDialog dialog = new JDialog((Frame) null, "Color Table");
		dialog.add(new JScrollPane(table));
		dialog.setLocationRelativeTo(owner);
		dialog.pack();
		dialog.setVisible(true);

	} // end showColorTable

} // end class
