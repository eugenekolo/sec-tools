package steganabara.filter;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SpringLayout;

import steganabara.SpringUtilities;

public class BitMaskDialog extends JDialog implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -3185486959658850463L;
	private static final String[] channels = { "Alpha", "Red", "Green", "Blue" };
	private final JCheckBox[][] argb;
	private JCheckBox amp;
	private BitMaskOptions options;

	public BitMaskDialog(Frame owner, String title) {

		super(owner, title, true);

		setLayout(new BorderLayout());
		argb = new JCheckBox[4][8];

		JPanel panel = new JPanel();
		panel.setLayout(new SpringLayout());
		for (int j = 0; j < 4; j++) {
			panel.add(new JLabel(channels[j], JLabel.TRAILING));
			for (int i = 0; i < 8; i++)
				panel.add(argb[j][i] = new JCheckBox());
		}
		SpringUtilities.makeCompactGrid(panel, 4, 9, 3, 3, 3, 3);
		add(panel, BorderLayout.CENTER);

		panel = new JPanel();
		amp = new JCheckBox("Amplify");
		panel.add(amp);
		JButton button = new JButton("OK");
		button.setActionCommand("ok");
		button.addActionListener(this);
		panel.add(button);
		button = new JButton("Cancel");
		button.setActionCommand("cancel");
		button.addActionListener(this);
		panel.add(button);
		add(panel, BorderLayout.SOUTH);
		pack();
		setResizable(false);

	} // end constructor

	public BitMaskOptions getOptions() {

		return options;

	} // end getOptions

	public void actionPerformed(ActionEvent e) {

		String cmd = e.getActionCommand();
		if (cmd.equals("ok")) {
			long value = 0;
			for (int j = 0; j < 4; j++)
				for (int i = 0; i < 8; i++)
					value = (value << 1) | (argb[j][i].isSelected() ? 1 : 0);
			options = new BitMaskOptions(value, amp.isSelected());
		}
		setVisible(false);

	} // end actionPerformed

	public static BitMaskOptions showBitMaskDialog(Component target, String title) {

		BitMaskDialog dialog = new BitMaskDialog(null, title);
		dialog.setLocationRelativeTo(target);
		dialog.setVisible(true);
		return dialog.getOptions();

	} // end showBitMaskDialog

} // end class
