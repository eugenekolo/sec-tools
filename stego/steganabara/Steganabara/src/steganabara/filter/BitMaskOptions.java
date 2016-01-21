package steganabara.filter;

public class BitMaskOptions {

	private long mask;
	private boolean amplify;

	public BitMaskOptions(long mask, boolean amplify) {
		this.mask = mask;
		this.amplify = amplify;
	}

	public long getMask() {
		return mask;
	}

	public boolean isAmplify() {
		return amplify;
	}

}
