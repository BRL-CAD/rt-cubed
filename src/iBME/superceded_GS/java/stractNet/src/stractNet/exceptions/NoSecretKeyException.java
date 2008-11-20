package stractNet.exceptions;

public class NoSecretKeyException extends SNException {

	public NoSecretKeyException(String arg0, Throwable arg1) {
		super(arg0, arg1);
	}

	public NoSecretKeyException(String arg0) {
		super(arg0);
	}

	public NoSecretKeyException(Throwable arg0) {
		super(arg0);
	}

	static final long serialVersionUID = 1L;
}
