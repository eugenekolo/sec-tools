package steganabara.menus;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.KeyStroke;

import steganabara.Stevironment;
import steganabara.color.ColorTableMenuItem;
import steganabara.filter.BitMaskMenuItem;
import steganabara.filter.ColorMapMenuItem;
import steganabara.histogram.HistogramMenuItem;
import steganabara.image.ImageContainer;

public final class MenuMaker {

	public static final String EXIT_COMMAND = "exit";

	public static JMenu createFileMenu(ActionListener listener, ImageContainer container) {

		JMenuItem jmiExit = new JMenuItem("Exit", KeyEvent.VK_X);
		jmiExit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, ActionEvent.CTRL_MASK));
		jmiExit.setActionCommand(EXIT_COMMAND);
		jmiExit.addActionListener(listener);

		JMenu menu = new JMenu("File");
		menu.setMnemonic(KeyEvent.VK_F);
		menu.add(new OpenMenuItem(container));
		menu.add(new SaveAsMenuItem(container));
		menu.addSeparator();
		menu.add(jmiExit);
		return menu;

	}

	public static JMenu createEditMenu(ImageContainer container) {

		JMenu menu = new JMenu("Edit");
		menu.setMnemonic(KeyEvent.VK_E);
		menu.add(new CopyMenuItem(container));
		menu.add(new PasteMenuItem(container));
		return menu;

	}

	public static JMenu createFilterMenu(ImageContainer container) {

		JMenu menu = new JMenu("Filter");
		menu.setMnemonic(KeyEvent.VK_F);
		menu.add(new BitMaskMenuItem(container));
		menu.add(new ColorMapMenuItem(container));
		return menu;

	}

	public static JMenu createAnalyseMenu(ImageContainer container) {

		JMenu menu = new JMenu("Analyse");
		menu.setMnemonic(KeyEvent.VK_A);
		menu.add(new ZoomMenu(container));
		menu.addSeparator();
		menu.add(Stevironment.getInstance().getColorExplorerMenuItem());
		menu.addSeparator();
		menu.add(new HistogramMenuItem(container));
		menu.add(new ColorTableMenuItem(container));
		return menu;

	}

	public static JPopupMenu createImagePopupMenu(ImageContainer container) {

		JPopupMenu menu = new JPopupMenu();
		menu.add(new CopyMenuItem(container));
		menu.add(new SaveAsMenuItem(container));
		menu.addSeparator();
		menu.add(new ZoomMenu(container));
		menu.addSeparator();
		menu.add(new HistogramMenuItem(container));
		menu.add(new ColorTableMenuItem(container));
		return menu;

	}

}
