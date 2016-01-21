package steganabara.color;

import java.awt.image.BufferedImage;
import java.util.Hashtable;

import javax.swing.table.AbstractTableModel;

public class ColorTableModel extends AbstractTableModel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4333206710336232054L;
	private final String[] columnNames = { "Color", "Alpha", "Red", "Green", "Blue", "Frequency" };
	private final Integer[][] data;

	public ColorTableModel(BufferedImage image) {

		Hashtable<Integer, Integer> h = ColorCounter.count(image);
		data = new Integer[h.size()][2];
		int count = 0;
		for (int key : h.keySet()) {

			int value = h.get(key);
			int rgb = key;
			data[count][0] = rgb;
			data[count++][1] = value;

		} // end for
		h = null;

	} // end constructor

	public String getColumnName(int col) {

		return columnNames[col];

	} // end getColumnName

	public int getRowCount() {

		return data.length;

	} // end getRowCount

	public int getColumnCount() {

		return columnNames.length;

	} // end getColumnCount

	public Class<Integer> getColumnClass(int columnIndex) {

		return Integer.class;

	} // end getColumnClass

	public Object getValueAt(int row, int col) {

		switch (col) {
		case 0:
			return String.format("%08X", data[row][0]).toUpperCase();
		case 1:
			return (data[row][0] >> 24) & 0xFF;
		case 2:
			return (data[row][0] >> 16) & 0xFF;
		case 3:
			return (data[row][0] >> 8) & 0xFF;
		case 4:
			return data[row][0] & 0xFF;
		default:
			return data[row][1];
		}

	} // end getValueAt

	public boolean isCellEditable(int row, int col) {

		return false;

	} // end isCellEditable

} // end class
