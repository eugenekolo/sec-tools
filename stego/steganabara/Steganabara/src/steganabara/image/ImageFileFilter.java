package steganabara.image;

import java.io.File;

import javax.swing.filechooser.FileFilter;

public class ImageFileFilter extends FileFilter {

	public static final String[] extensions = { "bmp", "gif", "jpg", "jpeg", "png", "wbmp" };
	public static final String description = "All supported images (BMP, GIF, JPG, PNG)";

	@Override
	public boolean accept(File f) {

		if (f.isDirectory()) return true;
		String filename = f.getName();
		int i = filename.lastIndexOf('.');
		if (i < 0 || i == filename.length() - 1) return false;
		String extension = filename.substring(i + 1);
		for (i = 0; i < extensions.length; i++)
			if (extensions[i].equals(extension)) return true;
		return false;

	} // end accept

	@Override
	public String getDescription() {

		return description;

	} // end getDescription

} // end class
