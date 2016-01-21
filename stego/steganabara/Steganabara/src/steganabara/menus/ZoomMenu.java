package steganabara.menus;

import java.awt.event.KeyEvent;

import javax.swing.ButtonGroup;
import javax.swing.JMenu;

import steganabara.image.ImageContainer;

public class ZoomMenu extends JMenu {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6779339360496150646L;

	public ZoomMenu(ImageContainer container) {

		super("Zoom");
		ButtonGroup group = new ButtonGroup();
		setMnemonic(KeyEvent.VK_Z);
		for (float f : new float[] { 0.5f, 1, 1.5f, 2, 3, 4 }) {
			ZoomMenuItem item = new ZoomMenuItem(container, f);
			group.add(item);
			if (f == 1) group.setSelected(item.getModel(), true);
			add(item);
		}

	}

}
