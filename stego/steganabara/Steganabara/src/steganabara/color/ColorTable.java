package steganabara.color;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;

import javax.swing.JTable;
import javax.swing.table.TableModel;

import steganabara.filter.ColorMapMenuItem;

public class ColorTable extends JTable implements MouseListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2530941080127747720L;
	private final BufferedImage image;

	public ColorTable(TableModel model, BufferedImage image) {

		super(model);
		this.image = image;
		addMouseListener(this);

	} // end constructor

	public void mouseClicked(MouseEvent e) {

		if (e.getClickCount() != 2) return;
		int row = rowAtPoint(e.getPoint());
		int color = (int) Long.parseLong(getValueAt(row, 0).toString(), 16);
		ColorMapMenuItem.showColorMapDialog(this, image, color);

	} // end mouseClicked

	public void mouseEntered(MouseEvent e) {
	}

	public void mouseExited(MouseEvent e) {
	}

	public void mousePressed(MouseEvent e) {
	}

	public void mouseReleased(MouseEvent e) {
	}

} // end class
