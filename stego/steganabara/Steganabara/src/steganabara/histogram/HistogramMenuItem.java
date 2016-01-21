package steganabara.histogram;

import java.awt.Component;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;

import javax.swing.JDialog;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import steganabara.image.ImageContainer;

public class HistogramMenuItem extends JMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -7409472295450531339L;
	private final ImageContainer container;

	public HistogramMenuItem(ImageContainer container) {

		super("Histogram", KeyEvent.VK_H);
		this.container = container;
		setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_H, ActionEvent.CTRL_MASK));
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		showHistogramDialog(container.getComponent(), container.getImage());

	} // end actionPerformed

	/**
	 * Show the histogram frame
	 */
	public static void showHistogramDialog(Component owner, BufferedImage image) {

		if (image == null) return;
		JDialog dialog = new JDialog();
		dialog.setTitle("Histogram");
		dialog.setDefaultCloseOperation(JDialog.HIDE_ON_CLOSE);
		dialog.setLayout(new GridLayout(2, 2, 5, 5));
		dialog.add(new HistogramPanel(image, HistogramMode.GRAYSCALE));
		dialog.add(new HistogramPanel(image, HistogramMode.RED));
		dialog.add(new HistogramPanel(image, HistogramMode.GREEN));
		dialog.add(new HistogramPanel(image, HistogramMode.BLUE));
		dialog.setLocationRelativeTo(owner);
		dialog.pack();
		dialog.setResizable(false);
		dialog.setVisible(true);

	} // end showHistogramDialog

} // end class
