package steganabara.menus;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JRadioButtonMenuItem;

import steganabara.image.ImageContainer;

public class ZoomMenuItem extends JRadioButtonMenuItem implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 3594767624362070222L;
	private final ImageContainer container;
	private final float zoom;

	public ZoomMenuItem(ImageContainer container, float zoom) {

		super(Float.toString(zoom));
		this.container = container;
		this.zoom = zoom;
		addActionListener(this);

	} // end constructor

	public void actionPerformed(ActionEvent e) {

		container.setZoom(zoom);

	} // end actionPerformed

} // end class
