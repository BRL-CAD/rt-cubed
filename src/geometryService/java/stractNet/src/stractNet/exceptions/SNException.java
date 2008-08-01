package stractNet.exceptions;

import stractNet.SNRoot;

public class SNException extends Exception {
	static final long serialVersionUID = 1L;


	public SNException(String arg0, Throwable arg1) {
		super(arg0, arg1);
		SNRoot.serr(arg1.getMessage(),0);
	}

	public SNException(String arg0) {
		super(arg0);
		SNRoot.serr(arg0,0);
	}

	public SNException(Throwable arg0) {
		super(arg0);
		SNRoot.serr(arg0.getMessage(),0);
	}

}
