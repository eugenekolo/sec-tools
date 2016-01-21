package steganabara.color;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;

import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;

import steganabara.image.ImageContainer;
import steganabara.image.ImagePanel;

public class ColorExplorerDialog extends JDialog implements MouseMotionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 8522189387475814641L;
	private static final int range = 4, block = 21;
	private static final int width = range * 2 + 1;
	private static final int size = block * width;
	private static final String rFormat = "X: %1$3d R: %2$3d %2$1c";
	private static final String gFormat = "Y: %1$3d G: %2$3d %2$1c";
	private static final String bFormat = "A: %1$3d B: %2$3d %2$1c";
	private static final String hFormat = "Hex: %08X";
	private static final Font font = new Font(Font.MONOSPACED, Font.BOLD, 14);
	private final ImagePanel panel;
	private final BufferedImage image;
	private final JLabel rLabel, gLabel, bLabel, hLabel;

	public ColorExplorerDialog() {

		setTitle("Color Explorer");
		setDefaultCloseOperation(HIDE_ON_CLOSE);
		setLayout(new BorderLayout());

		image = new BufferedImage(size, size, BufferedImage.TYPE_INT_ARGB);
		panel = new ImagePanel(image);
		add(panel, BorderLayout.CENTER);

		rLabel = new JLabel(String.format(rFormat, 0, 0));
		rLabel.setFont(font);
		rLabel.setHorizontalAlignment(JLabel.CENTER);
		gLabel = new JLabel(String.format(gFormat, 0, 0));
		gLabel.setFont(font);
		gLabel.setHorizontalAlignment(JLabel.CENTER);
		bLabel = new JLabel(String.format(bFormat, 0, 0));
		bLabel.setFont(font);
		bLabel.setHorizontalAlignment(JLabel.CENTER);
		hLabel = new JLabel(String.format(hFormat, 0));
		hLabel.setFont(font);
		hLabel.setHorizontalAlignment(JLabel.CENTER);

		JPanel textPanel = new JPanel(new GridLayout(4, 1, 2, 2));
		textPanel.add(rLabel);
		textPanel.add(gLabel);
		textPanel.add(bLabel);
		textPanel.add(hLabel);
		add(textPanel, BorderLayout.SOUTH);
		setResizable(false);
		pack();

	} // end constructor

	public void mouseDragged(MouseEvent e) {

		// Not interested

	} // end mouseDragged

	public void mouseMoved(MouseEvent e) {

		if (!isVisible()) return;
		Object o = e.getSource();
		if (!(o instanceof ImageContainer)) return;
		ImageContainer container = (ImageContainer) o;
		float zoom = container.getZoom();
		int x = (int) (e.getX() / zoom);
		int y = (int) (e.getY() / zoom);
		int rgb = container.getRGB(x, y);
		int alpha = (rgb >> 24) & 0xFF;
		int red = (rgb >> 16) & 0xFF;
		int green = (rgb >> 8) & 0xFF;
		int blue = rgb & 0xFF;
		rLabel.setText(String.format(rFormat, x, red));
		gLabel.setText(String.format(gFormat, y, green));
		bLabel.setText(String.format(bFormat, alpha, blue));
		hLabel.setText(String.format(hFormat, rgb));

		x -= range;
		y -= range;
		Graphics g = image.getGraphics();

		for (int i = 0; i < width; i++)
			for (int j = 0; j < width; j++) {
				g.setColor(new Color(container.getRGB(x + i, y + j)));
				g.fillRect(i * block, j * block, block, block);
			}
		g.setColor(Color.RED);
		g.drawLine(0, size / 2, size, size / 2);
		g.drawLine(size / 2, 0, size / 2, size);

		panel.repaint();

	} // end mouseMoved

} // end class
