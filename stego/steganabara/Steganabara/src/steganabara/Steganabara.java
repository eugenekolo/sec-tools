package steganabara;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import steganabara.image.ImagePanel;
import steganabara.menus.MenuMaker;

/**
 * Description: The Steganabara utility for steganalysis
 * 
 * @author quangntenemy
 * @since 5.0
 * @version 1.1.0 27/10/2007
 */

public final class Steganabara extends JFrame implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -3553947788109489130L;
	private ImagePanel panel;

	/**
	 * Create a new Steganabara
	 */
	public Steganabara() {

		super("Steganabara");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		initComponents();
		initMenus();
		pack();

	} // end constructor

	/**
	 * Initialize the GUI components
	 */
	private void initComponents() {

		setLayout(new BorderLayout());
		panel = new ImagePanel();
		JPanel test = new JPanel();
		test.add(panel);
		add(new JScrollPane(test), BorderLayout.CENTER);
		Stevironment.getInstance().registerImagePanel(panel);

	} // end initComponents

	/**
	 * Initialize the menus
	 */
	private void initMenus() {

		JMenuBar menuBar = new JMenuBar();
		menuBar.add(MenuMaker.createFileMenu(this, panel));
		menuBar.add(MenuMaker.createEditMenu(panel));
		menuBar.add(MenuMaker.createFilterMenu(panel));
		menuBar.add(MenuMaker.createAnalyseMenu(panel));
		setJMenuBar(menuBar);

	} // end initMenus

	/**
	 * Terminate the program
	 */
	private void exit() {

		System.exit(0);

	} // end exit

	public ImagePanel getPanel() {
		return panel;
	}

	public void actionPerformed(ActionEvent e) {

		String s = e.getActionCommand();
		if (s.equals(MenuMaker.EXIT_COMMAND)) exit();

	} // end actionPerformed

	public static void main(String[] args) {

		new Steganabara().setVisible(true);

	} // end main

} // end class
