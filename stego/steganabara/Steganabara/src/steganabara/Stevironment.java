package steganabara;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import steganabara.color.ColorExplorerDialog;
import steganabara.color.ColorExplorerMenuItem;
import steganabara.image.ImagePanel;

public final class Stevironment {

	private static final Stevironment instance = new Stevironment();
	private ColorExplorerDialog colorDialog;
	private ColorExplorerMenuItem colorExplorerMenuItem;

	/**
	 * Singleton constructor
	 */
	private Stevironment() {

		colorDialog = new ColorExplorerDialog();
		colorDialog.addWindowListener(new WindowAdapter() {

			public void windowClosing(WindowEvent e) {

				colorExplorerMenuItem.setSelected(false);

			} // end windowClosing

		});
		colorExplorerMenuItem = new ColorExplorerMenuItem(colorDialog);

	} // end initExternalComponents

	/**
	 * Get the Stevironment singleton instance
	 * 
	 * @return The singleton instance
	 */
	public static Stevironment getInstance() {

		return instance;

	}

	/**
	 * Register an image panel for color exploring
	 * 
	 * @param panel
	 *            The panel to register
	 */
	public void registerImagePanel(ImagePanel panel) {

		panel.addMouseMotionListener(colorDialog);

	} // end registerImagePanel

	/**
	 * Unregister an image panel
	 * 
	 * @param panel
	 *            The panel to register
	 */
	public void unregisterImagePanel(ImagePanel panel) {

		panel.removeMouseMotionListener(colorDialog);

	} // end unregisterImagePanel

	public ColorExplorerMenuItem getColorExplorerMenuItem() {

		return colorExplorerMenuItem;

	}

}
